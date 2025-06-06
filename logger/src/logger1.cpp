#include "include/logger1.hpp"
#include <thread>
#include <fstream>
#include <iostream>

std::shared_ptr<Logger1> Logger1::instance_ = nullptr;

std::shared_ptr<Logger1> Logger1::Instance() {
    if (!instance_) {
        instance_ = std::make_shared<Logger1>();
    }

    return instance_;
}

Logger1::~Logger1() {
    {
        std::lock_guard lock(logger_mutex_);
        is_working_ = false;
        cv_logger_.notify_all();
    }
    
    if (work_thread_ && work_thread_->joinable()) {
        work_thread_->join();
    }

}

void Logger1::Add(Data data) {
    std::unique_lock locker(logger_mutex_);
    buffer_.push(data);
    cv_logger_.notify_one();
    locker.unlock();
}

void Logger1::Run() {
    std::ofstream outFile(buffer_name_);
    outFile.close();
    work_thread_ = std::make_shared<std::thread>([this](){
        std::unique_lock locker(logger_mutex_);
        is_working_ = true;
        locker.unlock();
        Work();
    });
}

void Logger1::Work() {
    std::unique_lock locker(logger_mutex_);
    while (true) {
        cv_logger_.wait(locker, [this]{ 
            return !buffer_.empty() || !is_working_; 
        });
        
        if (!is_working_ && buffer_.empty()) {
            break;
        }
        
        if (!buffer_.empty()) {
            Data data = buffer_.front();
            buffer_.pop();
            locker.unlock();
            
            Write(data);
            
            locker.lock();
        }
    }

    is_end_ = true;
    cv_working_.notify_one();
    locker.unlock();
}

void Logger1::Write(Data &data) {
    std::ofstream outfile;
    outfile.open(buffer_name_, std::ios::app);
    outfile << data.info_;
    outfile.close();
}

void Logger1::End() {
    {
        std::lock_guard locker(logger_mutex_);
        is_working_ = false;
        cv_logger_.notify_one();
    }

    std::unique_lock locker(logger_mutex_);
    cv_working_.wait(locker, [this]{ return is_end_; });
    locker.unlock();

    if (work_thread_ && work_thread_->joinable()) {
        work_thread_->join();
        work_thread_ = nullptr;
    }
}
#include "include/logger2.hpp"
#include <thread>
#include <fstream>
#include <iostream>

std::shared_ptr<Logger2> Logger2::instance_ = nullptr;

std::shared_ptr<Logger2> Logger2::Instance() {
    if (!instance_) {
        instance_ = std::make_shared<Logger2>();
    }

    return instance_;
}

Logger2::~Logger2() {
    {
        std::lock_guard lock(logger_mutex_);
        is_working_ = false;
        cv_logger_.notify_all();
    }
    
    if (work_thread_ && work_thread_->joinable()) {
        work_thread_->join();
    }

}

void Logger2::Add(Data data) {
    std::unique_lock locker(logger_mutex_);
    cv_logger_.wait(locker, [this]{ return current_size_ < max_buffer_size_; });
    buffer_.push(data);
    current_size_++;
    cv_logger_.notify_one();
    locker.unlock();
}

void Logger2::Run() {
    std::ofstream outFile(buffer_name_);
    outFile.close();
    work_thread_ = std::make_shared<std::thread>([this](){
        std::unique_lock locker(logger_mutex_);
        is_working_ = true;
        locker.unlock();
        Work();
    });
}

void Logger2::Work() {
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
            current_size_--;
            cv_logger_.notify_one();
            locker.unlock();
            Write(data);
            
            locker.lock();
        }
    }

    is_end_ = true;
    cv_working_.notify_one();
    locker.unlock();
}

void Logger2::Write(Data &data) {
    std::ofstream outfile;
    outfile.open(buffer_name_, std::ios::app);
    outfile << data.info_;
    outfile.close();
}

void Logger2::End() {
    {
        std::lock_guard locker(logger_mutex_);
        is_working_ = false;
        cv_logger_.notify_all();
    }

    std::unique_lock locker(logger_mutex_);
    cv_working_.wait(locker, [this]{ return is_end_; });
    locker.unlock();

    if (work_thread_ && work_thread_->joinable()) {
        work_thread_->join();
        work_thread_ = nullptr;
    }
}
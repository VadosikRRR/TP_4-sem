#include "include/logger3.hpp"
#include <thread>
#include <fstream>
#include <iostream>

std::shared_ptr<Logger3> Logger3::instance_ = nullptr;

std::shared_ptr<Logger3> Logger3::Instance() {
    if (!instance_) {
        instance_ = std::make_shared<Logger3>();
    }

    return instance_;
}

Logger3::~Logger3() {
    End();
}

void Logger3::Add(Data data) {
    std::lock_guard locker(logger_mutex_);
    buffer_.push(data);
}

void Logger3::Run() {
    std::ofstream outFile(buffer_name_);
    outFile.close();
    work_thread_ = std::make_shared<std::thread>([this](){
        std::unique_lock locker(logger_mutex_);
        is_working_ = true;
        locker.unlock();
        Work();
    });
}

void Logger3::Work() {
    while (true) {
        std::unique_lock locker(logger_mutex_);
        if (!is_working_ && buffer_.empty()) {
            return;
        }
        
        if (buffer_.empty()) {
            locker.unlock();
            std::this_thread::yield();
            continue;
        }
        
        Data data = buffer_.front();
        buffer_.pop();  
        locker.unlock();
        Write(data);
    }
}

void Logger3::Write(Data &data) {
    std::ofstream outfile;
    outfile.open(buffer_name_, std::ios::app);
    outfile << data.info_;
    outfile.close();
}

void Logger3::End() {
    {
        std::lock_guard locker(logger_mutex_);
        is_working_ = false;
    }

    if (work_thread_ && work_thread_->joinable()) {
        work_thread_->join();
        work_thread_ = nullptr;
    }
}
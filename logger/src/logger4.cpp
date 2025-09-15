#include "include/logger4.hpp"
#include <thread>
#include <fstream>
#include <iostream>

std::shared_ptr<Logger4> Logger4::instance_ = nullptr;

std::shared_ptr<Logger4> Logger4::Instance() {
    if (!instance_) {
        instance_ = std::make_shared<Logger4>();
    }

    return instance_;
}

Logger4::~Logger4() {
    End();
}

void Logger4::Add(Data data) {
    while (true) {
        std::unique_lock locker(logger_mutex_);
        if (current_size_ < max_buffer_size_) {
            buffer_.push(data);
            current_size_++;
            return;
        }
        
        locker.unlock();
        std::this_thread::yield();
    }
}

void Logger4::Run() {
    std::ofstream outFile(buffer_name_);
    outFile.close();
    work_thread_ = std::make_shared<std::thread>([this](){
        std::unique_lock locker(logger_mutex_);
        is_working_ = true;
        locker.unlock();
        Work();
    });
}

void Logger4::Work() {
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
        current_size_--;
        locker.unlock();
        Write(data);
    }
}

void Logger4::Write(Data &data) {
    std::ofstream outfile;
    outfile.open(buffer_name_, std::ios::app);
    outfile << data.info_;
    outfile.close();
}

void Logger4::End() {
    {
        std::lock_guard locker(logger_mutex_);
        is_working_ = false;
    }

    if (work_thread_ && work_thread_->joinable()) {
        work_thread_->join();
        work_thread_ = nullptr;
    }
}
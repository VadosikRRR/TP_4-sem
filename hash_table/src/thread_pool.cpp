#include "include/thread_pool.hpp"
#include <thread>

std::shared_ptr<ThreadPool> ThreadPool::instance_ = nullptr;

std::shared_ptr<ThreadPool> ThreadPool::Instance() {
    if (!instance_) {
        instance_ = std::make_shared<ThreadPool>();
    }
    
    return instance_;
}

ThreadPool::~ThreadPool() {
    Wait();
}

void ThreadPool::Wait() {
    std::lock_guard locker(threads_mutex_);
    for (auto &thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    
    threads_.clear();
}

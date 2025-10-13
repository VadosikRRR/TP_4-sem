#include "include/thread_pool.hpp"
#include "include/determinant.hpp"


void StartThread(Matrix matrix, 
    int &result,
    int current_deep_level,
    int &thread_pool,
    bool is_paralel = true);

std::shared_ptr<ThreadPool> ThreadPool::instance_ = nullptr;

ThreadPool & ThreadPool::Instance() {
    if (!instance_) {
        instance_ = std::make_shared<ThreadPool>();
    }
    
    return *instance_;
}

void ThreadPool::DeterminantInNewThread(
    std::vector<std::thread> &threads, 
    Matrix matrix, 
    int &result,
    int current_deep_level, 
    bool is_paralel) {
    std::unique_lock locker(thread_pool_mutex_);
    if (thread_pool_ <= 0 && current_deep_level > max_thread_deepth_level_) {
        locker.unlock();
        throw std::exception(); //"The conditions for creation are unacceptable";
    }

    thread_pool_--;
    locker.unlock();
    threads.emplace_back(
        StartThread,
        matrix,
        std::ref(result),
        current_deep_level,
        std::ref(thread_pool_),
        is_paralel);
}

void StartThread(
    Matrix matrix, 
    int &result,
    int current_deep_level,
    int &thread_pool, 
    bool is_paralel) {
    ThreadPool &link_thread_pool = ThreadPool::Instance();
    Determinant(matrix, result, current_deep_level + 1, is_paralel);
    std::lock_guard locker(link_thread_pool.GetMutex());
    thread_pool++;
}

std::mutex & ThreadPool::GetMutex() {
    return thread_pool_mutex_;
}

void ThreadPool::SetThreadPool(int new_thread_number) {
    if (new_thread_number >= 0) {
        thread_pool_ = new_thread_number;
    }
}

void ThreadPool::SetMaxDepth(int max_thread_deepth_level) {
    if (max_thread_deepth_level >= 0) {
        max_thread_deepth_level_ = max_thread_deepth_level;
    }
}

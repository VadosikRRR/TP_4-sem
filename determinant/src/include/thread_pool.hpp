#pragma once
#include "matrix.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include <memory>


class ThreadPool {
private:
    static std::shared_ptr<ThreadPool> instance_;
    int thread_pool_ = 4;
    int max_thread_deepth_level_ = 3;
    std::mutex thread_pool_mutex_;
public:
    static ThreadPool & Instance();
    std::mutex & GetMutex();
    void SetThreadPool(int new_thread_number);
    void SetMaxDepth(int max_thread_deepth_level);
    void DeterminantInNewThread(
        std::vector<std::thread> &threads, 
        Matrix matrix, 
        int &result,
        int current_deep_level,
        bool is_paralel = true);
};

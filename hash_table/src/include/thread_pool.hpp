#pragma once
#include "list.hpp"
#include <memory>
#include <mutex>
#include <thread>
#include <list>

class ThreadPool {
private:
    int thread_number_ = 1000;
    std::mutex thread_number_mutex_;
    std::list<std::thread> threads_;
    std::mutex threads_mutex_;
    static std::shared_ptr<ThreadPool> instance_;
public:
    ~ThreadPool();
    static std::shared_ptr<ThreadPool> Instance();
    void Wait();
    template<typename Func, typename DataType>// List --- плохо, как шаблонный параметр 90(пакетджтаск)
    void Complete(Func function, DataType data, List &list) {
        std::unique_lock locker(thread_number_mutex_);
        if (thread_number_ <= 0) {
            locker.unlock();
            function(data, std::ref(list));
            return;
        }

        thread_number_--;
        locker.unlock();
        std::unique_lock locker_threads(threads_mutex_);
        threads_.emplace_back([this](Func function, DataType data, List &list) {
            function(data, list); 
            std::unique_lock locker(thread_number_mutex_);
            thread_number_++;
            locker.unlock();
        }, function, data, std::ref(list));
        locker_threads.unlock();
    };
};

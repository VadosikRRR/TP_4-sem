#pragma once
#include "data.hpp"
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>


class Logger1 {
private:
    bool is_end_ = false;
    bool is_working_ = false;
    std::string buffer_name_ = "buffer.txt";
    std::queue<Data> buffer_;
    std::mutex logger_mutex_;
    std::condition_variable cv_logger_;
    std::condition_variable cv_working_;
    std::shared_ptr<std::thread> work_thread_;
    static std::shared_ptr<Logger1> instance_;

    void Work();
    void Write(Data &data);
public:
    ~Logger1();
    void Run();
    void Add(Data data);
    void End();
    static std::shared_ptr<Logger1> Instance();
};

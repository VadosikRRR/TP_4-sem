#pragma once
#include "data.hpp"
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <fstream>


class Logger4 {
private:
    bool is_end_ = false;
    bool is_working_ = false;
    int max_buffer_size_ = 10;
    int current_size_ = 0;
    std::string buffer_name_ = "buffer.txt";
    std::queue<Data> buffer_;
    std::mutex logger_mutex_;
    std::shared_ptr<std::thread> work_thread_;
    static std::shared_ptr<Logger4> instance_;

    void Work();
    void Write(Data &data);
public:
    ~Logger4();
    void Run();
    void Add(Data data);
    void End();
    static std::shared_ptr<Logger4> Instance();
};

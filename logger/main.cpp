#include "src/include/data.hpp"
#include "src/include/logger1.hpp"
#include "src/include/logger2.hpp"
#include "src/include/logger3.hpp"
#include "src/include/logger4.hpp"
#include <thread>
#include <list>
#include <chrono>
#include <format>


// std::shared_ptr<Logger1> LOGGER = Logger1::Instance();
// std::shared_ptr<Logger2> LOGGER = Logger2::Instance();
// std::shared_ptr<Logger3> LOGGER = Logger3::Instance();
std::shared_ptr<Logger4> LOGGER = Logger4::Instance();

void task(double max_period, int max_iteration, int number) {
    // in ms
    double period = max_period * 1000 * rand() / RAND_MAX;

    for (size_t i = 0; i < max_iteration; i++) {
        auto start = std::chrono::system_clock::now();
        std::string start_time = std::format("{:%H:%M:%S}", start);
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(period));
        auto end = std::chrono::system_clock::now();
        std::string end_time = std::format("{:%H:%M:%S}", end);

        Data data {
            std::string("This function number is ") +
            std::to_string(number) + 
            std::string(". My period is ") +
            std::to_string(period / 1000) +
            std::string(". I started at ") +
            start_time + 
            std::string(". Finished - ") + 
            end_time +
            std::string(".\n")
        };

        LOGGER->Add(data);
    }
}

int main() {
    LOGGER->Run();

    double max_period = 0.1;
    int thread_number = 12;
    int max_iteration = 25;
    std::list<std::thread> threads;
    for (int k = 1; k <= thread_number; k++) {
        threads.emplace_back(task, max_period, max_iteration, k);
    }

    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    LOGGER->End();
    return 0;
}

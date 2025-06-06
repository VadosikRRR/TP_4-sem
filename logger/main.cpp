#include "src/include/data.hpp"
#include "src/include/logger1.hpp"
#include "src/include/logger2.hpp"
#include "src/include/logger3.hpp"
#include "src/include/logger4.hpp"
#include <cstdlib>
#include <thread>
#include <list>
#include <chrono>

// std::shared_ptr<Logger1> LOGGER = Logger1::Instance();
std::shared_ptr<Logger2> LOGGER = Logger2::Instance();
// std::shared_ptr<Logger3> LOGGER = Logger3::Instance();
// std::shared_ptr<Logger4> LOGGER = Logger4::Instance();

void task(double max_period, int max_iteration, int number) {
    // in ms
    double period = max_period * rand() / RAND_MAX;

    for (size_t i = 0; i < max_iteration; i++) {
        std::this_thread::sleep_for(std::chrono::seconds());
        Data data {
            std::string("This function number is ") +
            std::to_string(number) + 
            std::string(". My period is") +
            std::to_string(period) +
            std::string(". That's all)\n")
        };

        LOGGER->Add(data);
    }
}

int main() {
    LOGGER->Run();

    double max_period = 0.5;
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

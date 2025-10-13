#include "src/include/programs.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <list>

double EasyProgramTest() {
    std::vector<int> array {1, -2, 3, -4, 5, -6, 7, -8};
    std::list<std::thread> threads;
    int iterations = 20;
    double all_time = 0;
    clock_t start_time = clock();
    for (int i = 0; i < iterations; i++) {
        threads.emplace_back(EasyProgram, std::ref(array));
    }

    for(auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    clock_t end_time = clock();
    all_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    return all_time / iterations;
}

double WithBigMutexProgramTest() {
    std::vector<int> array {1, -2, 3, -4, 5, -6, 7, -8};
    std::list<std::thread> threads;
    int iterations = 20;
    double all_time = 0;
    clock_t start_time = clock();
    for (int i = 0; i < iterations; i++) {
        threads.emplace_back(WithBigMutexProgram, std::ref(array));
    }

    for(auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    clock_t end_time = clock();
    all_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    return all_time / iterations;
}

double TryLockProgramTest() {
    std::vector<int> array {1, -2, 3, -4, 5, -6, 7, -8};
    InitMutexes(array.size());
    std::list<std::thread> threads;
    int iterations = 20;
    double all_time = 0;
    clock_t start_time = clock();
    for (int i = 0; i < iterations; i++) {
        threads.emplace_back(TryLockProgram, std::ref(array));
    }

    for(auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    clock_t end_time = clock();
    all_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    return all_time / iterations;
}

double ProtocolProgramTest() {
    std::vector<int> array {1, -2, 3, -4, 5, -6, 7, -8};
    InitMutexes(array.size());
    std::list<std::thread> threads;
    int iterations = 20;
    double all_time = 0;
    clock_t start_time = clock();
    for (int i = 0; i < iterations; i++) {
        threads.emplace_back(ProtocolProgram, std::ref(array));
    }

    for(auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    clock_t end_time = clock();
    all_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    return all_time / iterations;
}


int main() {
    // std::cout << std::to_string(EasyProgramTest()) << std::endl;
    // std::cout << std::to_string(WithBigMutexProgramTest()) << std::endl;
    std::cout << std::to_string(TryLockProgramTest()) << std::endl;
    // std::cout << std::to_string(ProtocolProgramTest()) << std::endl;

    return 0;
}

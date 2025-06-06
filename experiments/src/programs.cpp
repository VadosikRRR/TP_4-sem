#include "include/programs.hpp"
#include <cstdlib>
#include <thread>
#include <mutex>
#include <memory>
#include <algorithm>

bool BlockMutexes(std::mutex &mutex1, std::mutex &mutex2, std::mutex &mutex3);

std::vector<int> GetThreeRandomIndexes(int length);
std::mutex ARRAY_MUTEX;
std::vector<std::shared_ptr<std::mutex>> MUTEXES;
std::once_flag start_flag;

void InitMutexes(int length) {
    MUTEXES.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        MUTEXES.emplace_back(std::make_shared<std::mutex>());
    }
}

void ProtocolProgram(std::vector<int> &array) {
    int length = array.size();
    std::vector<int> indexes = GetThreeRandomIndexes(length);
    std::sort(indexes.begin(), indexes.end());
    std::lock_guard locker1(*MUTEXES[indexes[0]]);
    std::lock_guard locker2(*MUTEXES[indexes[1]]);
    std::lock_guard locker3(*MUTEXES[indexes[2]]);

    int sum = 0;
    for (size_t ind: indexes) {
        sum += array[ind];
    }

    for (size_t ind: indexes) {
        array[ind] = sum;
    }   
}

bool BlockMutexes(
    std::mutex &mutex1,
    std::mutex &mutex2,
    std::mutex &mutex3
) {
    if (!mutex1.try_lock()) {
        return false;
    }

    if (!mutex2.try_lock()) {
        mutex1.unlock();
        return false;
    }

    if (!mutex3.try_lock()) {
        mutex2.unlock();
        mutex1.unlock();
        return false;
    }
    
    return true;
}

void TryLockProgram(std::vector<int> &array) {
    int length = array.size();
    std::vector<int> indexes;
    while (true) {
        indexes = GetThreeRandomIndexes(length);
        // std::sort(indexes.begin(), indexes.end());
        if (!BlockMutexes(
            *MUTEXES[indexes[0]],
            *MUTEXES[indexes[1]],
            *MUTEXES[indexes[2]]
        )) {
            std::this_thread::yield();
            continue;
        }

        int sum = 0;
        for (size_t ind: indexes) {
            sum += array[ind];
        }

        for (size_t ind: indexes) {
            array[ind] = sum;
        }

        MUTEXES[indexes[2]]->unlock();
        MUTEXES[indexes[1]]->unlock();
        MUTEXES[indexes[0]]->unlock();
        return;
    }
}

void WithBigMutexProgram(std::vector<int> &array) {
    int length = array.size();
    std::vector<int> indexes = GetThreeRandomIndexes(length);
    int sum = 0;
    std::lock_guard locker(ARRAY_MUTEX);
    for (size_t ind: indexes) {
        sum += array[ind];
    }

    for (size_t ind: indexes) {
        array[ind] = sum;
    }
}

void EasyProgram(std::vector<int> &array) {
    int length = array.size();
    std::vector<int> indexes = GetThreeRandomIndexes(length);
    int sum = 0;
    for (size_t ind: indexes) {
        sum += array[ind];
    }

    for (size_t ind: indexes) {
        array[ind] = sum;
    }
}

std::vector<int> GetThreeRandomIndexes(int length) {
    std::vector<int> indexes {-1, -1, -1};
    int cnt = 0;
    while(cnt != 3) {
        int ind = rand() % length;
        if (ind != indexes[0] &&
            ind != indexes[1] &&
            ind != indexes[2]) {
                indexes[cnt] = ind;
                cnt++;
            }
    }

    return indexes;
}

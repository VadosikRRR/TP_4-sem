#include "include/matrix.hpp"
#include <thread>
#include <mutex>
#include <memory>
#include <cstdlib>
#include <iostream>


int Matrix::thread_pool_ = 4;
int Matrix::max_thread_deepth_level_ = 3;
std::mutex Matrix::thread_pool_mutex_;

Matrix::Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data) {
    height_ = height >= 1 ? height : 1;
    width_ = width >= 1 ? width : 1;
    data_ = matrix_data;
}

void Matrix::Determinant(int &result, int current_deep_level) {
    if (height_ != width_) {
        result = -20; //
        return;
    }

    if (height_ == 1) {
        result = data_[0][0];
        return;
    }
    
    std::vector<int> minor_determinants(width_, 0);
    DeterminantByRow(minor_determinants, current_deep_level);

    double deletrminant = 0;
    int sign = 1;
    for (size_t column = 0; column < width_; column++) {
        deletrminant += sign * data_[0][column] * minor_determinants[column];
        sign *= -1;
    }
    
    result = deletrminant;
}

void Matrix::DeterminantByRow(std::vector<int> &minor_determinants, int current_deep_level) {
    std::vector<std::thread> threads;
    current_deep_level++;
    for (size_t column = 0; column < width_; column++) {
        if (data_[0][column] == 0) {
            minor_determinants[column] = 0;
            continue;
        }

        Matrix minor = GetMinor(0, column);
        std::unique_lock<std::mutex> locker(Matrix::thread_pool_mutex_);
        if (thread_pool_ > 0 && current_deep_level <= max_thread_deepth_level_) {
            thread_pool_--;
            locker.unlock();
            auto minor_determinant { [](Matrix minor, 
                                          int current_deep_level, 
                                          int &result) 
                                          { minor.Determinant(result, current_deep_level);
                                            std::lock_guard<std::mutex> locker(Matrix::thread_pool_mutex_);
                                            thread_pool_++; }};
            threads.emplace_back(minor_determinant, minor, 
            current_deep_level, std::ref(minor_determinants[column]));
        } else {
            locker.unlock();
            minor.Determinant(minor_determinants[column], current_deep_level);
        }
    }

    for (auto &thread : threads) {
        thread.join();
    }
}

Matrix Matrix::GetMinor(int row, int column) {
    std::vector<std::vector<int>> minor_data = data_;
    for (size_t row = 0; row < height_; row++) {
        minor_data[row].erase(minor_data[row].begin() + column);
    }

    minor_data.erase(minor_data.begin() + row);
    return {height_ - 1, width_ - 1, minor_data};
}

int Matrix::GetRowNumber() {
    return height_;
}

int Matrix::GetColumnNumber() {
    return width_;
}

int Matrix::GetNumber(int row, int column) {
    return data_[row][column];
}

Matrix CreateMatrix(int row_number, int column_number) {
    std::vector<std::vector<int>> data(row_number, std::vector<int>(column_number, 0));
    for (size_t row = 0; row < row_number; row++) {
        for (size_t column = 0; column < column_number; column++) {
            data[row][column] = (rand() % 10) - 5;
        }
    }
    
    return {row_number, column_number, data};
}

void Matrix::SetThreadPool(int thread_number) {
    if (thread_number >= 0) {
        thread_pool_ = thread_number;
    }
}

void Matrix::SetMaxDeepth(int new_max_deepth) {
    if (new_max_deepth >= 1) {
        max_thread_deepth_level_ = new_max_deepth;
    }
}

void PrintMatrix(Matrix &matrix) {
    for (size_t i = 0; i < matrix.GetRowNumber(); i++) {
        for (size_t i1 = 0; i1 < matrix.GetColumnNumber(); i1++) {
            std::cout << matrix.GetNumber(i, i1) << ' ';
        }
        
        std::cout << std::endl;
    }
}
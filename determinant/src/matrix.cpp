#include "include/matrix.hpp"
#include <thread>
#include <memory>
#include <cstdlib>
#include <iostream>


int Matrix::thread_pool_ = 7;
int Matrix::max_thread_deepth_level_ = 20;

Matrix::Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data) {
    height_ = height >= 1 ? height : 1;
    width_ = width >= 1 ? width : 1;
    data_ = matrix_data;
}

void Matrix::Determinant(double &result, int current_deep_level) {
    if (height_ != width_) {
        result = -20; //
        return;
    }

    if (height_ == 1) {
        result = data_[0][0];
        return;
    }
    
    std::vector<double> minor_determinants(width_, 0);
    DeterminantByRow(minor_determinants, current_deep_level);

    double deletrminant = 0;
    int sign = 1;
    for (size_t column = 0; column < width_; column++) {
        deletrminant += sign * data_[0][column] * minor_determinants[column];
        sign *= -1;
    }
    
    result = deletrminant;
}

void Matrix::DeterminantByRow(std::vector<double> &minor_determinants, int current_deep_level) {
    for (size_t column = 0; column < width_; column++) {
        if (data_[0][column] == 0) {
            minor_determinants[column] = 0;
            continue;
        }
        
        current_deep_level++;
        if (thread_pool_ > 0 && current_deep_level <= max_thread_deepth_level_) {
            std::shared_ptr<Matrix> ptr_minor = std::make_shared<Matrix>(GetMinor(0, column));
            thread_pool_--;
            auto minor_determinant { [](std::shared_ptr<Matrix> ptr_minor, 
                                          int current_deep_level, 
                                          double &result) 
                                          { ptr_minor->Determinant(result, current_deep_level);
                                            thread_pool_++; }};
            std::thread determinant_thread(minor_determinant, ptr_minor, current_deep_level, std::ref(minor_determinants[column]));
            determinant_thread.join();
        } else {
            Matrix minor = GetMinor(0, column);
            minor.Determinant(minor_determinants[column], current_deep_level);
        }
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

void PrintMatrix(Matrix &matrix) {
    for (size_t i = 0; i < matrix.GetRowNumber(); i++) {
        for (size_t i1 = 0; i1 < matrix.GetColumnNumber(); i1++) {
            std::cout << matrix.GetNumber(i, i1) << ' ';
        }
        
        std::cout << std::endl;
    }
}
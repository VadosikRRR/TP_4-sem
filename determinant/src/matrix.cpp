#include "include/matrix.hpp"
#include <thread>
#include <mutex>
#include <memory>
#include <cstdlib>
#include <iostream>


Matrix::Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data) {
    height_ = height >= 1 ? height : 1;
    width_ = width >= 1 ? width : 1;
    data_ = matrix_data;
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

int Matrix::operator()(int row, int column) {
    if (row >= height_ || column >= width_) {
        throw std::exception(); //"incorrect indexes";
    }

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
            std::cout << matrix(i, i1) << ' ';
        }
        
        std::cout << std::endl;
    }
}

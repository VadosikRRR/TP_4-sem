#include "include/matrix.hpp"


Matrix::Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data) {
    height_ = height >= 1 ? height : 1;
    width_ = width >= 1 ? width : 1;
    data_ = matrix_data;
}

double Matrix::Determinate() {
    if (height_ != width_) {
        return -20;
    }

    if (height_ == 1) {
        return data_[0][0];
    }
    
    double deletrminate = 0;
    int sign = 1;
    for (size_t colum = 0; colum < width_; colum++) {   
        std::vector<std::vector<int>> minor_data = data_;
        minor_data.erase(minor_data.begin());
        for (size_t row = 0; row < height_; row++) {
            minor_data[row].erase(minor_data[row].begin() + colum);
        }
        Matrix minor {height_ - 1, width_ - 1, minor_data};
        double minor_deletrminate = minor.Determinate();
        deletrminate += sign * data_[0][colum] *  minor_deletrminate ;
        sign *= -1;
    }
    
    return deletrminate;
}
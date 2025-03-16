#pragma once
#include <vector>


class Matrix {
private:
    int height_;
    int width_;
    std::vector<std::vector<int>> data_;

public:
    Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data);
    double Determinate();
};

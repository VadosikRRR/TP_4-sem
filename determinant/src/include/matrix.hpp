#pragma once
#include <vector>
#include <mutex>


class Matrix {
private:
    // Следует не смешивать две разных по смыслу вещи. Матрица скорее просто структура или класс
    int height_;
    int width_;
    std::vector<std::vector<int>> data_;
public:
    Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data);
    int GetRowNumber();
    int GetColumnNumber();
    Matrix GetMinor(int row, int column);
    int operator()(int row, int column);
};

Matrix CreateMatrix(int row_number, int column_number);
void PrintMatrix(Matrix &matrix);

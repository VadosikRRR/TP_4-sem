#pragma once
#include <vector>


class Matrix {
private:
    static int thread_pool_;
    static int max_thread_deepth_level_;
    int height_;
    int width_;
    std::vector<std::vector<int>> data_;
    Matrix GetMinor(int row, int column);
    void DeterminantByRow(std::vector<double> &minor_determinants, int current_deep_level = 1);
public:
    Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data);
    void Determinant(double &result, int current_deep_level = 1);
    int GetRowNumber();
    int GetColumnNumber();
    int GetNumber(int row, int column);
};

Matrix CreateMatrix(int row_number, int column_number);
void PrintMatrix(Matrix &matrix);

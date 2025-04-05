#pragma once
#include <vector>
#include <mutex>


class Matrix {
private:
    // Следует не смешивать две разных по смыслу вещи. Матрица скорее просто структура или класс
    static int thread_pool_;
    static int max_thread_deepth_level_;
    static std::mutex thread_pool_mutex_;
    int height_;
    int width_;
    std::vector<std::vector<int>> data_;
    Matrix GetMinor(int row, int column);
    void DeterminantByRow(std::vector<int> &minor_determinants, int current_deep_level = 1);
public:
    Matrix(int height, int width, std::vector<std::vector<int>> &matrix_data);
    void Determinant(int &result, int current_deep_level = 1);
    int GetRowNumber();
    int GetColumnNumber();
    int GetNumber(int row, int column);
    static void SetThreadPool(int thread_number);
    static void SetMaxDeepth(int new_max_deepth);
};

Matrix CreateMatrix(int row_number, int column_number);
void PrintMatrix(Matrix &matrix);

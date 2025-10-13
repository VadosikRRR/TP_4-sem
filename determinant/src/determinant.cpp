#include "include/determinant.hpp"
#include "include/thread_pool.hpp"

#include <exception>


void DeterminantByRowParalel(Matrix &matrix, std::vector<int> &minor_determinants, int current_deep_level);
void DeterminantByRow(Matrix &matrix, std::vector<int> &minor_determinants, int current_deep_level);

void Determinant(Matrix &matrix, int &result, int current_deep_level, bool is_parralel) {
    int height = matrix.GetRowNumber();
    int width = matrix.GetColumnNumber();
    if (height != width) {
        throw std::exception();
        // "Incorrect size"
    }

    if (width == 1) {
        result = matrix(0, 0);
        return;
    }
    
    std::vector<int> minor_determinants(width, 0);
    if (is_parralel) {
        DeterminantByRowParalel(matrix, minor_determinants, current_deep_level);
    } else {
        DeterminantByRow(matrix, minor_determinants, current_deep_level);
    }

    int deletrminant = 0;
    int sign = 1;
    for (size_t column = 0; column < width; column++) {
        deletrminant += sign * matrix(0, column) * minor_determinants[column];
        sign *= -1;
    }
    
    result = deletrminant;
}

void DeterminantByRowParalel(Matrix &matrix, std::vector<int> &minor_determinants, int current_deep_level) {
    std::vector<std::thread> threads;
    for (size_t column = 0; column < matrix.GetColumnNumber(); column++) {
        if (matrix(0, column) == 0) {
            minor_determinants[column] = 0;
            continue;
        }

        ThreadPool &thread_pool = ThreadPool::Instance();
        Matrix minor = matrix.GetMinor(0, column);

        try {
            thread_pool.DeterminantInNewThread(
                threads,
                minor,
                minor_determinants[column],
                current_deep_level + 1,
                true
            );
        }
        catch(const std::exception& e) {
            Determinant(minor, minor_determinants[column], current_deep_level + 1, false);
        }
    }

    for (auto &thread : threads) {
        thread.join();
    }
}

void DeterminantByRow(Matrix &matrix, std::vector<int> &minor_determinants, int current_deep_level) {
    for (size_t column = 0; column < matrix.GetColumnNumber(); column++) {
        if (matrix(0, column) == 0) {
            minor_determinants[column] = 0;
            continue;
        }
        
        Matrix minor = matrix.GetMinor(0, column);
        Determinant(minor, minor_determinants[column], current_deep_level + 1, false);
    }
}

#include "src/include/test.hpp"
#include "src/include/matrix.hpp"
#include "src/include/determinant.hpp"
#include "src/include/thread_pool.hpp"
#include <vector>
#include <iostream>


void tests() {
    correctnessTest1();
    correctnessTest2();
    correctnessTest3();
}

void correctnessTest1() {
    std::vector<std::vector<int>> data = {{1, 2, 3},
                                          {-1, 2, -3},
                                          {4, -5, 6}};
    Matrix matrix {3, 3, data};
    int real_determinant = -24;
    int calculate_determinant = 0;
    Determinant(matrix, calculate_determinant);
    if (calculate_determinant == real_determinant) {
        std::cout << "Correctness test 1 is passed" << std::endl;
        return;
    }

    std::cout << "Correctness test 1 is falled" << std::endl;
    std::cout << "Expected: " << real_determinant << std::endl;
    std::cout << "Received: " << calculate_determinant << std::endl;
}

void correctnessTest2() {
    std::vector<std::vector<int>> data = {{7, 5, 3, 9, 1},
                                          {1, 2, 3, 2, 1},
                                          {9, 5, 1, 7, 3},
                                          {4, 5, 6, 8, 2},
                                          {0, 3, 4, 5, 9}};
    Matrix matrix {5, 5, data};
    int real_determinant = 80;
    int calculate_determinant = 0;
    Determinant(matrix, calculate_determinant);
    if (calculate_determinant == real_determinant) {
        std::cout << "Correctness test 2 is passed" << std::endl;
        return;
    }

    std::cout << "Correctness test 2 is falled" << std::endl;
    std::cout << "Expected: " << real_determinant << std::endl;
    std::cout << "Received: " << calculate_determinant << std::endl;
}

void correctnessTest3() {
    std::vector<std::vector<int>> data = {{7, 5, 3, 9, 1, -2, 0},
                                          {0, 2, 3, 2, 1, 0, -5},
                                          {0, 0, 1, 7, 3, 10, 2},
                                          {0, 0, 0, 8, 2, 7, 7},
                                          {0, 0, 0, 0, 9, 0, 0},
                                          {0, 0, 0, 0, 0, -1, 2},
                                          {0, 0, 0, 0, 0, 0, 2}};
    Matrix matrix {7, 7, data};
    int real_determinant = -2016;
    int calculate_determinant = 0;
    Determinant(matrix, calculate_determinant);
    if (calculate_determinant == real_determinant) {
        std::cout << "Correctness test 2 is passed" << std::endl;
        return;
    }

    std::cout << "Correctness test 2 is falled" << std::endl;
    std::cout << "Expected: " << real_determinant << std::endl;
    std::cout << "Received: " << calculate_determinant << std::endl;
}

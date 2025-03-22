#include "src/include/test.hpp"
#include "src/include/matrix.hpp"
#include <vector>
#include <iostream>


double EPS = 1E-4;


void tests() {
    correctnessTest1();
    correctnessTest2();
}

void correctnessTest1() {
    std::vector<std::vector<int>> data = {{1, 2, 3},
                                          {-1, 2, -3},
                                          {4, -5, 6}};
    Matrix matrix {3, 3, data};
    double real_determinant = -24;
    double calculate_determinant = 0;
    matrix.Determinant(calculate_determinant);
    if (calculate_determinant - real_determinant < EPS) {
        std::cout << "Correctness test 1 is passed" << std::endl;
        return;
    }

    std::cout << "Correctness test 1 is falled" << std::endl;
    std::cout << "Expected: " << -24 << std::endl;
    std::cout << "Received: " << calculate_determinant << std::endl;
}

void correctnessTest2() {
    std::vector<std::vector<int>> data = {{7, 5, 3, 9, 1},
                                          {1, 2, 3, 2, 1},
                                          {9, 5, 1, 7, 3},
                                          {4, 5, 6, 8, 2},
                                          {0, 3, 4, 5, 9}};
    Matrix matrix {5, 5, data};
    double real_determinant = 80;
    double calculate_determinant = 0;
    matrix.Determinant(calculate_determinant);
    if (calculate_determinant - real_determinant < EPS) {
        std::cout << "Correctness test 2 is passed" << std::endl;
        return;
    }

    std::cout << "Correctness test 2 is falled" << std::endl;
    std::cout << "Expected: " << 80 << std::endl;
    std::cout << "Received: " << calculate_determinant << std::endl;
}

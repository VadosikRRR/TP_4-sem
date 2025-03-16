#include "src/include/matrix.hpp"
#include <vector>
#include <iostream>
#include <ctime>


int main() {
    

    // std::vector<std::vector<int>> data1 = {{1, 2, 3, 4, 5},
    //                                        {5, 4, 3, 2, 1},
    //                                        {0, 1, 2, 3, 0},
    //                                        {0, 3, 2, 1, 0},
    //                                        {3, 2, 1, 2, 3}};
    // Matrix new_matrix = {static_cast<int>(data.size()), static_cast<int>(data[0].size()), data};
    
    double sum = 0;
    for (int i = 0; i < 20; i++) {
        std::cout << "Test "<< i + 1 << std::endl;
        Matrix matrix = CreateMatrix(10, 10);
        // PrintMatrix(matrix);
        double result = 0;
        clock_t start_time = clock();
        matrix.Determinant(result);
        clock_t end_time = clock();
        std::cout << result << std::endl;
        sum += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        std::cout << std::endl << std::endl;
    }
    std::cout << sum/20 << std::endl;
    
    return 0;
}
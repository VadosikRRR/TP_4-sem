#include "src/include/matrix.hpp"
#include <vector>
#include <iostream>


int main() {
    std::vector<std::vector<int>> data = {{1, 2},
                                          {2, 1}};
    Matrix new_matrix = {static_cast<int>(data.size()), static_cast<int>(data[0].size()), data};
    std::cout << new_matrix.Determinate() << std::endl;
}
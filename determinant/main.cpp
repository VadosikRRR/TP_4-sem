#include "src/include/matrix.hpp"
#include "src/include/test.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <fstream>


struct Row {
    int size_matrix_;
    int iteration_number_;
    int thread_number_;
    int max_deepth_;
    double time_;
};


int MAX_THREAD_NUMBER = 15;
std::vector<Row> data;


void TestTime(int size_matrix, int iteration_number) {
    for (int thread_number = 0; thread_number < MAX_THREAD_NUMBER; thread_number++) {
        Matrix::SetThreadPool(thread_number);
        for (int max_deepth = 1; max_deepth <= size_matrix; max_deepth++) {
            Matrix::SetMaxDeepth(max_deepth);
            double all_time = 0;
            for (int iterate = 0; iterate < iteration_number; iterate++) {
                Matrix matrix = CreateMatrix(size_matrix, size_matrix);
                int result = 0;
                clock_t start_time = clock();
                matrix.Determinant(result);
                clock_t end_time = clock();
                all_time += static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
            }

            data.push_back({size_matrix, iteration_number, thread_number,
                            max_deepth, all_time / iteration_number});
        }
    }
}


void SaveToCSV(std::string path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи!" << std::endl;
        return;
    }

    file << "Matrix size,Iteration number,Thread number,Max deepth,Time\n"; 

    for (auto &row : data) {
        file << row.size_matrix_ << "," << row.iteration_number_ << ","
             << row.thread_number_ << "," << row.max_deepth_ << ","
             << row.time_ << "\n";   
    }

    file.close();
    std::cout << "CSV-файл успешно создан: " << path << std::endl;
}


int main() {   
    for (int size_matrix = 3; size_matrix <= 5; size_matrix++) {
        std::cout << "Matrix size: " << size_matrix << std::endl;
        TestTime(size_matrix, 20);
    }

    SaveToCSV("result.csv");
    tests();
    return 0;
}

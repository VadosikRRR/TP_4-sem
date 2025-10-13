#include "test.hpp"
#include <iostream>


int main() {
    Test tester = Test();
    if (tester.GeneralTest()) {
        std::cout << "✅ All tests are competed\n";
    } else {
        std::cout << "❌ There is a mistake\n";
    }

    return 0;
}

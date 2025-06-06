#include "test.hpp"
#include "src/include/data.hpp"
#include "src/include/exception.hpp"
#include <iostream>


Test::Test() {}

bool Test::TestSize1() {
    try {
        HashTable table {10};
        return true;
    } catch(const std::exception &e) {
        return false;
    }

    return false;
}

bool Test::TestSize2() {
    try {
        HashTable table {-5};
        return false;
    } catch(const IncorrectHashTableSizeException &e) {
        return true;
    }
    
    return false;
}

bool Test::TestSize3() {
    try {
        HashTable table {20000};
        return true;
    } catch(const std::exception &e) {
        return false;
    }

    return false;
}

bool Test::TestSize() {
    bool result1 = TestSize1();
    result1 ? std::cout << "✅ TestSize1 is competed\n" : std::cout << "❌ TestSize1 is not completed\n";
    bool result2 = TestSize2();
    result2 ? std::cout << "✅ TestSize2 is competed\n" : std::cout << "❌ TestSize2 is not completed\n";
    bool result3 = TestSize3();
    result3 ? std::cout << "✅ TestSize3 is competed\n" : std::cout << "❌ TestSize3 is not completed\n";
    return result1 && result2 && result3;
}

bool Test::TestPut1() {
    HashTable table {20};
    Data data {0, "TestPut1"};
    bool must_be_false = table.Check(data);
    table.Put(data);
    bool must_be_true = table.Check(data);
    return !must_be_false && must_be_true;
}

bool Test::TestPut2() {
    HashTable table {10};
    Data data {-5, "TestPut2"};
    bool must_be_false = table.Check(data);
    table.Put(data);
    bool must_be_true = table.Check(data);
    return !must_be_false && must_be_true;
}

bool Test::TestPut3() {
    HashTable table {15};
    Data data {112312, "TestPut3"};
    bool must_be_false = table.Check(data);
    table.Put(data);
    bool must_be_true = table.Check(data);
    return !must_be_false && must_be_true;
}

bool Test::TestPut4() {
    HashTable table {8};
    Data data1 {1, "TestPut4_1"};
    Data data2 {2, "TestPut4_2"};
    bool must_be_false1 = table.Check(data1);
    bool must_be_false2 = table.Check(data2);
    table.Put(data1);
    bool must_be_true1 = table.Check(data1);
    bool must_be_false3 = table.Check(data2);
    table.Put(data2);
    bool must_be_true2 = table.Check(data1);
    bool must_be_true3 = table.Check(data2);
    return !must_be_false1 && !must_be_false2 && !must_be_false3 &&
           must_be_true1 && must_be_true2 && must_be_true3;
}

bool Test::TestPut5() {
    HashTable table {1};
    Data data1 {1, "TestPut5"};
    Data data2 {2, "TestPut5"};
    bool must_be_false1 = table.Check(data1);
    bool must_be_false2 = table.Check(data2);
    table.Put(data1);
    bool must_be_true1 = table.Check(data1);
    bool must_be_false3 = table.Check(data2);
    table.Put(data2);
    bool must_be_true2 = table.Check(data1);
    bool must_be_true3 = table.Check(data2);
    return !must_be_false1 && !must_be_false2 && !must_be_false3 &&
           must_be_true1 && must_be_true2 && must_be_true3;
}

bool Test::TestPut() {
    bool result1 = TestPut1();
    result1 ? std::cout << "✅ TestPut1 is competed\n" : std::cout << "❌ TestPut1 is not completed\n";
    bool result2 = TestPut2();
    result2 ? std::cout << "✅ TestPut2 is competed\n" : std::cout << "❌ TestPut2 is not completed\n";
    bool result3 = TestPut3();
    result3 ? std::cout << "✅ TestPut3 is competed\n" : std::cout << "❌ TestPut3 is not completed\n";
    bool result4 = TestPut4();
    result4 ? std::cout << "✅ TestPut4 is competed\n" : std::cout << "❌ TestPut4 is not completed\n";
    bool result5 = TestPut5();
    result5 ? std::cout << "✅ TestPut5 is competed\n" : std::cout << "❌ TestPut5 is not completed\n";
    return result1 && result2 && result3 && result4 && result5;
}

bool Test::TestCheck1() {
    HashTable table {7};
    Data data {1000, "TestCheck1"};
    return !table.Check(data);
}

bool Test::TestCheck2() {
    HashTable table {80};
    Data data {-45, "TestCheck2"};
    bool must_be_false = table.Check(data);
    table.Put(data);
    bool must_be_true = table.Check(data);
    return !must_be_false && must_be_true;
}
 
bool Test::TestCheck3() {
    HashTable table {43};
    Data data {1, "TestCheck3"};
    bool must_be_false1 = table.Check(data);
    table.Put(data);
    bool must_be_true1 = table.Check(data);
    table.Remove(data);
    bool must_be_false2 = table.Check(data);
    table.Put(data);
    bool must_be_true2 = table.Check(data);
    return !must_be_false1 && must_be_true1 && !must_be_false2 && must_be_true2;
}

bool Test::TestCheck4() {
    HashTable table {3};
    Data data1 {6, "TestCheck4_1"};
    Data data2 {2, "TestCheck4_2"};
    bool must_be_false1 = table.Check(data1);
    bool must_be_false2 = table.Check(data2);
    table.Put(data1);
    bool must_be_true1 = table.Check(data1);
    bool must_be_false3 = table.Check(data2);
    return !must_be_false1 && !must_be_false2 && !must_be_false3 && must_be_true1;
}

bool Test::TestCheck() {
    bool result1 = TestCheck1();
    result1 ? std::cout << "✅ TestCheck1 is competed\n" : std::cout << "❌ TestCheck1 is not completed\n";
    bool result2 = TestCheck2();
    result2 ? std::cout << "✅ TestCheck2 is competed\n" : std::cout << "❌ TestCheck2 is not completed\n";
    bool result3 = TestCheck3();
    result3 ? std::cout << "✅ TestCheck3 is competed\n" : std::cout << "❌ TestCheck3 is not completed\n";
    bool result4 = TestCheck4();
    result4 ? std::cout << "✅ TestCheck4 is competed\n" : std::cout << "❌ TestCheck4 is not completed\n";
    return result1 && result2 && result3 && result4;
}

bool Test::TestRemove1() {
    HashTable hash_table {25};
    Data data {1, "TestRemove1"};
    hash_table.Put(data);
    bool must_be_true = hash_table.Check(data);
    hash_table.Remove(data);
    bool must_be_false = hash_table.Check(data);
    return must_be_true && !must_be_false;
}

bool Test::TestRemove2() {
    HashTable hash_table {25};
    Data data1 {5, "TestRemove2"};
    Data data2 {7, "TestRemove2"};
    hash_table.Put(data1);
    hash_table.Put(data2);
    bool must_be_true1 = hash_table.Check(data1);
    bool must_be_true2 = hash_table.Check(data2);
    hash_table.Remove(data1);
    bool must_be_false = hash_table.Check(data1);
    bool must_be_true3 = hash_table.Check(data2);
    return must_be_true1 && must_be_true2 && must_be_true3 && !must_be_false;
}

bool Test::TestRemove3() {
    HashTable hash_table {25};
    Data data1 {5, "TestRemove2"};
    Data data2 {5, "TestRemove3"};
    hash_table.Put(data1);
    hash_table.Put(data2);
    bool must_be_true1 = hash_table.Check(data1);
    bool must_be_true2 = hash_table.Check(data2);
    hash_table.Remove(data1);
    bool must_be_false = hash_table.Check(data1);
    bool must_be_true3 = hash_table.Check(data2);
    return must_be_true1 && must_be_true2 && must_be_true3 && !must_be_false;
}

bool Test::TestRemove4() {
    HashTable hash_table {25};
    Data data1 {5, "TestRemove2"};
    Data data2 {5, "TestRemove3"};
    Data data3{5, "TestRemove4"};
    hash_table.Put(data1);
    hash_table.Put(data2);
    hash_table.Put(data3);
    bool must_be_true1 = hash_table.Check(data1);
    bool must_be_true2 = hash_table.Check(data2);
    bool must_be_true3 = hash_table.Check(data3);
    hash_table.Remove(data2);
    bool must_be_true4 = hash_table.Check(data1);
    bool must_be_false1 = hash_table.Check(data2);
    bool must_be_true5 = hash_table.Check(data3);
    hash_table.Remove(data1);
    bool must_be_false2 = hash_table.Check(data1);
    bool must_be_false3 = hash_table.Check(data2);
    bool must_be_true6 = hash_table.Check(data3);
    return must_be_true1 && must_be_true2 && must_be_true3 &&
           must_be_true4 && must_be_true5 && must_be_true6 &&
           !must_be_false1 && !must_be_false2 && !must_be_false3;
}

bool Test::TestRemove5() {
    HashTable hash_table {25};
    Data data1 {5, "TestRemove2"};
    Data data2 {5, "TestRemove3"};
    Data data3{5, "TestRemove4"};
    hash_table.Put(data1);
    hash_table.Put(data2);
    hash_table.Put(data3);
    hash_table.Remove(data1);
    hash_table.Remove(data2);
    hash_table.Remove(data3);
    hash_table.Remove(data1);
    return true;
}

bool Test::TestRemove() {
    bool result1 = TestRemove1();
    result1 ? std::cout << "✅ TestRemove1 is competed\n" : std::cout << "❌ TestRemove1 is not completed\n";
    bool result2 = TestRemove2();
    result2 ? std::cout << "✅ TestRemove2 is competed\n" : std::cout << "❌ TestRemove2 is not completed\n";
    bool result3 = TestRemove3();
    result3 ? std::cout << "✅ TestRemove3 is competed\n" : std::cout << "❌ TestRemove3 is not completed\n";
    bool result4 = TestRemove4();
    result4 ? std::cout << "✅ TestRemove4 is competed\n" : std::cout << "❌ TestRemove4 is not completed\n";
    bool result5 = TestRemove5();
    result5 ? std::cout << "✅ TestRemove5 is competed\n" : std::cout << "❌ TestRemove5 is not completed\n";
    return result1 && result2 && result3 && result4 && result5;
}

bool Test::GeneralTest() {
    bool result1 = TestSize();
    result1 ? std::cout << "✅ TestSize is competed\n" : std::cout << "❌ TestSize is not completed\n";
    bool result2 = TestPut();
    result2 ? std::cout << "✅ TestPut is competed\n" : std::cout << "❌ TestPut is not completed\n";
    bool result3 = TestCheck();
    result3 ? std::cout << "✅ TestCheck is competed\n" : std::cout << "❌ TestCheck is not completed\n";
    bool result4 = TestRemove();
    result4 ? std::cout << "✅ TestRemove is competed\n" : std::cout << "❌ TestRemove is not completed\n";
    bool result5 = StressTest();
    result5 ? std::cout << "✅ StressTest is competed\n" : std::cout << "❌ StressTest is not completed\n";
    return result1 && result2 && result3;
}

bool Test::StressTest1() {
    HashTable hash_table {10};
    for (int i = 1; i <= 1000; i++) {        
        Data data {i, "Test"};
        hash_table.Put(data);
    }

    bool is_correct = true;
    for (int i = 1; i <= 1000; i++) {
        Data data {i, "Test"};
        is_correct = is_correct && hash_table.Check(data);
    }
    
    return is_correct;
}

bool Test::StressTest2() {
    int max = 40;
    HashTable hash_table {25};
    for (int i = 0; i < 1000; i++) {
        int rand1 = std::rand() % (max + 1);
        int rand2 = std::rand() % 3;
        Data data {rand1, "Test"};
        if (rand2 == 0) {
            hash_table.Put(data);
        } else if (rand2 == 1) {
            hash_table.Check(data);
        } else {
            hash_table.Remove(data);
        }
    }
    
    return true;
}

bool Test::StressTest() {
    bool result1 = StressTest1();
    bool result2 = StressTest2();
    result1 ? std::cout << "✅ StressTest1 is competed\n" : std::cout << "❌ StressTest1 is not completed\n";
    result2 ? std::cout << "✅ StressTest2 is competed\n" : std::cout << "❌ StressTest2 is not completed\n";
    return result1 && result2;
}
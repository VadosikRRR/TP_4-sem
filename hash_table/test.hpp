#pragma once
#include "src/include/hash_table.hpp"

class Test {
private:
public:
    Test();

    bool GeneralTest();

    bool TestSize();
    bool TestSize1();
    bool TestSize2();
    bool TestSize3();

    bool TestPut();
    bool TestPut1();
    bool TestPut2();
    bool TestPut3();
    bool TestPut4();
    bool TestPut5();

    bool TestCheck();
    bool TestCheck1();
    bool TestCheck2();
    bool TestCheck3();
    bool TestCheck4();

    bool TestRemove();
    bool TestRemove1();
    bool TestRemove2();
    bool TestRemove3();
    bool TestRemove4();
    bool TestRemove5();

    bool StressTest();
    bool StressTest1();
    bool StressTest2();
};

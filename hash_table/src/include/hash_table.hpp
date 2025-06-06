#pragma once
#include "data.hpp"
#include "list.hpp"
#include "thread_pool.hpp"
#include <vector>

class HashTable {
private:
    int size_;
    std::vector<List> data_;
    std::shared_ptr<ThreadPool> thread_pool_;
    int GetHash(Data &data);
public:
    HashTable(int size);
    ~HashTable();
    void Put(Data &data);
    void Remove(Data &data);
    bool Check(Data &data);
};

// константные ссылки передавать 
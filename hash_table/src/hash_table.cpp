#include "include/hash_table.hpp"
#include "include/exception.hpp"

HashTable::HashTable(int size) {
    if (size <= 0) {
        throw IncorrectHashTableSizeException("Incorrect hash table size.");
    }

    size_ = size;
    data_.resize(size_);
    thread_pool_ = ThreadPool::Instance();
}

HashTable::~HashTable() {
    thread_pool_->Wait();
}

int HashTable::GetHash(Data &data) {
    return abs(data.GetNumber()) % size_;
}

void HashTable::Put(Data &data) {
    int hash = GetHash(data);
    thread_pool_->Complete([](Data data, List &list) {list.Push(data);}, data, data_[hash]);
}

void HashTable::Remove(Data &data) {
    int hash = GetHash(data);
    thread_pool_->Complete([](Data data, List &list) {list.Erase(data);}, data, data_[hash]);
}

bool HashTable::Check(Data &data) {
    int hash = GetHash(data);
    thread_pool_->Wait();
    return data_[hash].Find(data);
}

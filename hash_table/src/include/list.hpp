#pragma once
#include "data.hpp"
#include <memory>
#include <mutex>

class List {
private:
    struct Node {
        Node(Data data, std::shared_ptr<Node> next_node);
        Data data_;
        std::shared_ptr<Node> next_node_;
        std::mutex node_mutex;
    };

    std::shared_ptr<Node> root_;
public:
    List();
    ~List();
    void Push(Data data);
    void Pop();
    void Clear();
    Data Front();
    bool Find(Data data);
    void Erase(Data data);
};

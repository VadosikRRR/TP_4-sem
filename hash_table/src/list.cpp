#include "include/list.hpp"
#include "include/exception.hpp"

List::Node::Node(Data data, std::shared_ptr<Node> next_node) {
    data_=data;
    next_node_ = next_node;
}

List::List() {
    root_ = std::make_shared<Node> (Data(), nullptr);
}

List::~List() {
    Clear();
}

void List::Push(Data data) {
    std::lock_guard locker_root(root_->node_mutex);
    std::shared_ptr<Node> new_node = std::make_shared<Node>(data, root_->next_node_);
    root_->next_node_ = new_node;
}

void List::Pop() {
    if (!root_->next_node_) {
        return;
    }
    std::lock_guard locker_root(root_->node_mutex);
    std::lock_guard locker_next(root_->next_node_->node_mutex);
    root_->next_node_ = (root_->next_node_)->next_node_;
}

void List::Clear() {
    while(root_->next_node_) {
        Pop();
    }
}

Data List::Front() {
    if (!root_->next_node_) {
        throw EmptyListException("List is empty");
    }

    return root_->next_node_->data_;
}

bool List::Find(Data data) { // более оптимально
    std::shared_ptr<Node> temp = root_;
    while (temp) {
        if (temp->data_ == data) {
            return true;
        }

        temp = temp->next_node_;
    }
    
    return false;
}

// void List::Erase(Data data) {
//     if (!root_->next_node_) {
//         return;
//     }

//     std::shared_ptr<Node> temp = root_;
//     while (temp->next_node_) {
//         if (temp->next_node_->data_ != data) {
//             temp = temp->next_node_;
//             continue;
//         }
        
//         std::lock_guard locker_temp(temp->node_mutex);
//         std::lock_guard locker_del(temp->next_node_->node_mutex);
//         temp->next_node_ = (temp->next_node_)->next_node_;
//         return;
//     }
// }

void List::Erase(Data data) {
    if (!root_->next_node_) {
        return;
    }

    std::shared_ptr<Node> prev = root_;
    std::unique_lock<std::mutex> lock_prev(prev->node_mutex);
    std::shared_ptr<Node> current = prev->next_node_;

    while (current) {
        std::unique_lock<std::mutex> lock_current(current->node_mutex);

        if (prev->next_node_ != current) {
            lock_current.unlock();
            current = prev->next_node_;
            continue;
        }

        if (current->data_ == data) {
            prev->next_node_ = current->next_node_;
            return;
        }

        lock_prev.unlock();
        prev = current;
        lock_prev = std::move(lock_current);
        current = current->next_node_;
    }
}

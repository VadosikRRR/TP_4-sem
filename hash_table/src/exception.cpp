#include "include/exception.hpp"

EmptyListException::EmptyListException(const std::string &message) : message_(message) {}

const char* EmptyListException::what() const noexcept {
    return message_.c_str();
}

IncorrectListIndexException::IncorrectListIndexException(const std::string &message) : message_(message) {}

const char* IncorrectListIndexException::what() const noexcept {
    return message_.c_str();
}

IncorrectHashTableSizeException::IncorrectHashTableSizeException(const std::string &message) : message_(message) {}

const char* IncorrectHashTableSizeException::what() const noexcept {
    return message_.c_str();
}

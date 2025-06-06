#pragma once
#include <exception>
#include <iostream>


class EmptyListException: public std::exception {
private:
    std::string message_;
public:
    EmptyListException(const std::string &message);
    const char* what() const noexcept override;
};


class IncorrectListIndexException: public std::exception {
private:
    std::string message_;
public:
    IncorrectListIndexException(const std::string &message);
    const char* what() const noexcept override;
};


class IncorrectHashTableSizeException: public std::exception {
private:
    std::string message_;
public:
    IncorrectHashTableSizeException(const std::string &message);
    const char* what() const noexcept override;
};

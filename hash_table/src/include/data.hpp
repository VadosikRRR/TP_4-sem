#pragma once
#include <iostream>

class Data {
private:
    int number_;
    std::string info_;
public:
    explicit Data(int number = 0, std::string info = "");
    void SetInfo(std::string new_info);
    void SetNumber(int new_number);
    int GetNumber();
    const std::string & GetInfo() const;

    bool operator ==(Data &data) const;
    bool operator !=(Data &data) const;
};

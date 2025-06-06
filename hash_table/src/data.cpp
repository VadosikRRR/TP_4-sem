#include "include/data.hpp"

Data::Data(int number, std::string info) : number_(number), info_(info) {}

void Data::SetInfo(std::string new_info) {
    info_ = new_info;
}

void Data::SetNumber(int new_number) {
    number_ = new_number;
}

int Data::GetNumber() {
    return number_;
}

const std::string & Data::GetInfo() const {
    return info_;
}

bool Data::operator ==(Data &data) const{
    return number_ == data.GetNumber() && info_ == data.GetInfo();
}

bool Data::operator !=(Data &data) const{
    return !(*this == data);
}

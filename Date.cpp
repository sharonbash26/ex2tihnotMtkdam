#include "Date.h"

Date::Date(std::string date) {
    _date = date;
}

Date::~Date() = default;

bool operator<(const Date &lhs, const Date &rhs) {
    return lhs._date < rhs._date;
}
bool operator>(const Date &lhs, const Date &rhs) {
    return lhs._date > rhs._date;
}
bool operator==(const Date &lhs, const Date &rhs) {
    return lhs._date == rhs._date;
}

std::ostream &operator<<(std::ostream &ostream, const Date &date) {
    ostream << date._date;
    return ostream;
}

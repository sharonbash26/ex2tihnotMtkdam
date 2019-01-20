#ifndef AP1_DATE_H
#define AP1_DATE_H

#include <iostream>
#include <string>

class Date {
public:
    /**
     * Format - YYYY-MM-DD
     * @param date - date string of format YYYY-MM-DD
     */
    Date(std::string date);
    ~Date();
    friend bool operator<(const Date &lhs, const Date &rhs);
    friend bool operator>(const Date &lhs, const Date &rhs);
    friend bool operator==(const Date &lhs, const Date &rhs);

    friend std::ostream& operator<<(std::ostream &ostream, const Date &date);
private:
    std::string _date;
};

#endif //AP1_DATE_H

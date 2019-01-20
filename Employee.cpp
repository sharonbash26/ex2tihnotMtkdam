#include <sstream>
#include <tuple>
#include "Employee.h"
#include "RW.h"

Employee::Employee(std::string id, Jobs title, int birthYear, int seniority, Employee *employer) : ID(id){
    _title = title;
    _birthYear = birthYear;
    _seniority = seniority;
    _employer = employer;
}

Employee::~Employee() {}

Jobs Employee::getTitle() {
    return _title;
}

int Employee::getBirthYear() {
    return _birthYear;
}

int Employee::getSeniority() {
    return _seniority;
}

Employee *Employee::getEmployer() {
    return _employer;
}

void Employee::setEmployer(Employee *e) {
    _employer = e;
}

std::string Employee::to_file() {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    std::stringstream ss;
    ss << getID() << SEP;
    ss << ((_employer) ? _employer->getID() : "") << SEP;
    ss << _title << SEP;
    ss << _birthYear << SEP;
    ss << _seniority;

    return ss.str();
}

std::tuple<Employee *, std::string> Employee::from_file(const std::string &line) {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    auto tokens = RW::split(line, SEP);
    if(tokens.size() !=5 ) {
        throw std::runtime_error("bad employee line");
    }

    std::string id = tokens[0];
    std::string employerID = tokens[1];
    Jobs title = static_cast<Jobs>(std::stoi(tokens[2]));
    int birthYear = std::stoi(tokens[3]);
    int seniority = std::stoi(tokens[4]);

    Employee* e = new Employee(id, title, birthYear, seniority, nullptr);
    return std::make_tuple(e, employerID);
}

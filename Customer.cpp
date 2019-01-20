//
// Created by sharon_i4 on 26/11/2018.
//

#include <sstream>
#include "Customer.h"
#include "RW.h"

Customer::Customer(std::string id, std::string fullName, int priority)
        : ID(id) {
    //call to construter of father
    //becase we inhert from her.
    _fullName = fullName;
    _priority = priority;
}

Customer::~Customer() {}

std::string Customer::getFullName() {
    return _fullName;
}

int Customer::getPriority() {
    return _priority;
}

void Customer::addReservation(Reservation *r) {
    _reservations.push_back(r);
}

std::vector<Reservation *> Customer::getReservations() {
    return _reservations;
}

std::string Customer::to_file() {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    std::stringstream ss;
    ss << getID() << SEP;
    ss << _fullName << SEP;
    ss << _priority;

    return ss.str();
}

Customer *Customer::from_file(const std::string &line) {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    auto tokens = RW::split(line, SEP);
    if(tokens.size() !=3 ) {
        throw std::runtime_error("bad customer line");
    }

    std::string id = tokens[0];
    std::string fullName = tokens[1];
    int priority = std::stoi(tokens[2]);
    return new Customer(id, fullName, priority);
}

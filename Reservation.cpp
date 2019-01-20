//
// Created by sharon_i4 on 26/11/2018.
//

#include <sstream>
#include <tuple>
#include "Reservation.h"
#include "RW.h"

#include "Customer.h"

Reservation::Reservation(std::string id, Customer *customer, Flight *flight, Classes _class, int maxBaggage)
        : ID(id) {
    _customer = customer;
    _flight = flight;
    this->_class = _class;
    _maxBaggage = maxBaggage;

}

Customer *Reservation::getCustomer() {
    return _customer;
}

Flight *Reservation::getFlight() {
    return _flight;
}

Classes Reservation::getClass() {
    return _class;
}

int Reservation::getMaxBaggage() {
    return _maxBaggage;
}

std::string Reservation::to_file() {
    std::stringstream ss;
    ss << getID() << SEP;
    ss << _class << SEP;
    ss << _maxBaggage << SEP;
    ss << _customer->getID() << SEP;
    ss << _flight->getID();
    return ss.str();
}

std::tuple<Reservation *, std::string, std::string> Reservation::from_file(const std::string &line) {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    auto tokens = RW::split(line, SEP);
    if (tokens.size() != 5) { // we expect specific number of tokens - id, class, maxbaggage, customerID, flightID - 5
        throw std::runtime_error("bad reservation line");
    }
    // now
    std::string id = tokens[0];
    Classes cls = static_cast<Classes>(std::stoi(tokens[1]));
    int maxBaggage = std::stoi(tokens[2]);
    std::string customerID = tokens[3];
    std::string flightID = tokens[4];
    return std::make_tuple(new Reservation(id, nullptr, nullptr, cls, maxBaggage), customerID, flightID);
}

void Reservation::setCustomer(Customer *c) {
    _customer = c;
}

void Reservation::setFlight(Flight *f) {
    _flight = f;
}




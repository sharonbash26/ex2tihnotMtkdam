//
// Created by sharon_i4 on 26/11/2018.
//

#include <sstream>
#include "Flight.h"
#include "RW.h"

Flight::Flight(std::string id, int modelNum, Date date, std::string source, std::string dest)
        : ID(id),//to call the constructer of father
          _modelNum{modelNum},
          _date{date},
          _source{source},
          _dest{dest} {}

Flight::~Flight() {}

int Flight::getModelNumber() {
    return _modelNum;
}

void Flight::addCrewMember(Employee *employee) {
    _assignedCrew.push_back(employee);
}

std::list<Employee *> Flight::getAssignedCrew() {
    return std::list<Employee*>(_assignedCrew.begin(), _assignedCrew.end());
}

Date Flight::getDate() {
    return _date;
}

std::string Flight::getSource() {
    return _source;
}

std::string Flight::getDestination() {
    return _dest;
}

void Flight::addReservation(Reservation *r) {
    _reservations.push_back(r);
}

std::list<Reservation *> Flight::getReservations() {
    return std::list<Reservation*>(_reservations.begin(), _reservations.end());
}

std::string Flight::to_file() {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    std::stringstream ss;
    ss << getID() << SEP;
    ss << _modelNum << SEP;
    ss << _date << SEP;
    ss << _source << SEP;
    ss << _dest << SEP;
    return ss.str();
}

Flight *Flight::from_file(const std::string &line) {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    auto tokens = RW::split(line, SEP);
    if(tokens.size() !=5 ) {
        throw std::runtime_error("bad flight line");
    }

    std::string id = tokens[0];
    int modelNum = std::stoi(tokens[1]);
    Date d = Date(tokens[2]);
    std::string source = tokens[3] ;
    std::string dest = tokens[4];
    return new Flight(id, modelNum, d, source, dest);
}


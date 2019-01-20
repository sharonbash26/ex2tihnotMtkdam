//
// Created by sharon_i4 on 26/11/2018.
//

#include <sstream>
#include "Plane.h"
#include "RW.h"

Plane::Plane(std::string id, int modelNum, int maxFirstClass, int maxEconomyClass, std::map<Jobs, int> crewNeeded)
        : ID(id) {
    _modelNum = modelNum;
    _maxFirstClass = maxFirstClass;
    _maxEconomyClass = maxEconomyClass;
    _crewNeeded = crewNeeded;
}

Plane::~Plane() = default;

int Plane::getModelNumber() {
    return _modelNum;
}

int Plane::getMaxFirstClass() {
    return _maxFirstClass;
}

int Plane::getMaxEconomyClass() {
    return _maxEconomyClass;
}

std::map<Jobs, int> Plane::getCrewNeeded() {
    return _crewNeeded;
}

std::string Plane::to_file() {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    std::stringstream ss;
    // write the normie values
    ss << getID() << SEP;
    ss << _modelNum << SEP;
    ss << _maxFirstClass << SEP;
    ss << _maxEconomyClass << SEP;

    // write the map
    ss << _crewNeeded[MANAGER] << SEP;
    ss << _crewNeeded[NAVIGATOR] << SEP;
    ss << _crewNeeded[FLY_ATTENDANT] << SEP;
    ss << _crewNeeded[PILOT] << SEP;
    ss << _crewNeeded[OTHER];
    return ss.str();
}

Plane *Plane::from_file(const std::string &line) {
    // as advised by private teacher - David Samuelson (it appears in other students code probably) - its not copy.
    auto tokens = RW::split(line, SEP);
    if(tokens.size() != 9) {
        throw std::runtime_error("bad plane line");
    }

    std::string id = tokens[0];
    int modelNum = std::stoi(tokens[1]);
    int maxFirst = std::stoi(tokens[2]);
    int maxEconomy = std::stoi(tokens[3]);

    std::map<Jobs, int> crewNeeded;
    crewNeeded[MANAGER] = std::stoi(tokens[4]);
    crewNeeded[NAVIGATOR] = std::stoi(tokens[5]);
    crewNeeded[FLY_ATTENDANT] = std::stoi(tokens[6]);
    crewNeeded[FLY_ATTENDANT] = std::stoi(tokens[7]);
    crewNeeded[OTHER] = std::stoi(tokens[8]);

    return new Plane(id, modelNum, maxFirst, maxEconomy, crewNeeded);
}








#ifndef AP1_PLANE_H
#define AP1_PLANE_H


#include <map>
#include "ID.h"
#include "Jobs.h"

class Plane : public ID{
public:
    Plane(std::string id, int modelNum, int maxFirstClass, int maxEconomyClass, std::map<Jobs, int> crewNeeded);
    ~Plane();

    int getModelNumber();
    int getMaxFirstClass();
    int getMaxEconomyClass();
    std::map<Jobs, int> getCrewNeeded();

    std::string to_file();
    static Plane *from_file(const std::string &line);

private:
    int _modelNum;
    int _maxFirstClass;
    int _maxEconomyClass;
    std::map<Jobs, int> _crewNeeded;
};


#endif //AP1_PLANE_H

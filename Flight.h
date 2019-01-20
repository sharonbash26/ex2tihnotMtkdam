#ifndef AP1_FLIGHT_H
#define AP1_FLIGHT_H

#include <vector>
#include <list>
#include "ID.h"
#include "Date.h"
#include "Employee.h"

class Reservation;

class Flight : public ID {
public:
    Flight(std::string id, int modelNum, Date date, std::string source, std::string dest);

    ~Flight();

    int getModelNumber();

    void addCrewMember(Employee *employee);
    std::list<Employee *> getAssignedCrew();

    Date getDate();

    std::string getSource();

    std::string getDestination();

    void addReservation(Reservation *r);
    std::list<Reservation *> getReservations();

    std::string to_file();
    static Flight* from_file(const std::string &line);

private:
    int _modelNum;
    std::vector<Employee *> _assignedCrew;
    std::vector<Reservation *> _reservations;
    Date _date;
    std::string _source;
    std::string _dest;

};


#endif //AP1_FLIGHT_H

#ifndef AP1_EX2_H
#define AP1_EX2_H
#include "Employee.h"
#include "Plane.h"
#include "Classes.h"
#include "Flight.h"
#include "Customer.h"

using namespace std;

class Ex2 {
public:
    virtual Employee *addEmployee(int seniority, int birth_year, string employer_id, Jobs title) = 0;
    virtual Employee *getEmployee(string id) = 0;

    virtual Plane *addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) = 0;
    virtual Plane *getPlane(string id) = 0;

    virtual Flight *addFlight(int model_number, Date date, string source, string destination) = 0;
    virtual Flight *getFlight(string id) = 0;

    virtual Customer *addCustomer(string full_name, int priority) = 0;
    virtual Customer *getCustomer(string id) = 0;

    virtual Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage) = 0;
    virtual Reservation *getReservation(string id) = 0;

    virtual void exit() = 0;

    virtual ~Ex2() {}
};

#endif //AP1_EX2_H

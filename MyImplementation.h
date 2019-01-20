
#ifndef AP1_MYIMPLEMENTATION_H
#define AP1_MYIMPLEMENTATION_H


#include "Ex2.h"

class MyImplementation : public Ex2 {
public:
    MyImplementation();

    Employee *addEmployee(int seniority, int birth_year, string employer_id, Jobs title) override;
    Employee *getEmployee(string id) override;

    Plane *addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) override;
    Plane *getPlane(string id) override;
    std::vector<Plane *> getPlaneByModel(int modelNum);

    Flight *addFlight(int model_number, Date date, string source, string destination) override;
    Flight *getFlight(string id) override;

    Customer *addCustomer(string full_name, int priority) override;
    Customer *getCustomer(string id) override;

    Reservation *addResevation(string customerId, string flightId, Classes cls, int max_baggage) override;
    Reservation *getReservation(string id) override;

    void exit() override;

private:
    unsigned long _curr_id;
    vector<Employee *> _employees;
    vector<Plane *> _planes;
    vector<Flight *> _flights;
    vector<Customer *> _customers;
    vector<Reservation *> _reservations;
    string getCurrID();
};


#endif //AP1_MYIMPLEMENTATION_H

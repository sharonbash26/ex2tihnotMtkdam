
#ifndef AP1_CUSTOMER_H
#define AP1_CUSTOMER_H


#include <vector>
#include "Reservation.h"

class Customer :public ID{
public:
    Customer(std::string id, std::string fullName,int priority);
    ~Customer();

    std::string getFullName();
    int getPriority();

    void addReservation(Reservation *r);
    std::vector<Reservation  *> getReservations();

    std::string to_file();
    static Customer* from_file(const std::string &line);

private:
    std::string _fullName;
    int _priority;
    std::vector<Reservation *> _reservations;

};


#endif //AP1_CUSTOMER_H

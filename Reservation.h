#ifndef AP1_RESERVATION_H
#define AP1_RESERVATION_H

#include "ID.h"
#include "Flight.h"
#include "Classes.h"

class Customer;

class Reservation : public ID {
public:
    Reservation(std::string id, Customer *customer, Flight *flight, Classes _class, int maxBaggage);

    ~Reservation() = default;

    Customer *getCustomer();
    void setCustomer(Customer *c);

    Flight *getFlight();
    void setFlight(Flight *f);

    Classes getClass();

    int getMaxBaggage();

    std::string to_file();
    static std::tuple<Reservation*, std::string, std::string> from_file(const std::string &line);

private:
    Customer *_customer;
    Flight *_flight;
    Classes _class;
    int _maxBaggage;


};


#endif //AP1_RESERVATION_H

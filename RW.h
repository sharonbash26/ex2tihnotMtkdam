
#ifndef AP1_RWUTIL_H
#define AP1_RWUTIL_H

#include <string>
#include <vector>
#include "Plane.h"
#include "Employee.h"
#include "Reservation.h"

#define SEP '|'

#define FILE_ID "id.txt"
#define FILE_PLANE "planes.txt"
#define FILE_EMP "employees.txt"
#define FILE_CUSTOMER "customers.txt"
#define FILE_FLIGHT "flights.txt"
#define FILE_RES "reservations.txt"
#define FILE_ASSIGN "assignments.txt"

struct DataFile {
    unsigned long id;
    std::vector<Plane *> planes;
    std::vector<Employee *> employees;
    std::vector<Customer *> customers;
    std::vector<Flight *> flights;
    std::vector<Reservation *> reservations;
};

class RW {
public:
    static std::vector<std::string> split(const std::string &tosplit, char sep);
    static void write(unsigned long id,
                      const std::vector<Plane *> &planes,
                      const std::vector<Employee *> &employees,
                      const std::vector<Customer *> &customers,
                      const std::vector<Flight *> &flights,
                      const std::vector<Reservation *> &reservations);

    static DataFile read();

private:
    static void writeID(unsigned long id, const char *fname);
    static void writeAssignments(const std::vector<Flight *> &flights, const char *fname);

    static unsigned long readID(const char *fname);

    static std::vector<Employee *> readEmployees(const char *fname);

    static std::vector<Reservation *> readReservations(const char *fname,
                                                       std::vector<Customer *> &customers,
                                                       std::vector<Flight *> &flights);

    static void readAssignments(const char *fname,
                                std::vector<Flight *> &flights,
                                const std::vector<Employee *> &employees);

};


#endif //AP1_RWUTIL_H

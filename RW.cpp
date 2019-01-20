#include <sstream>
#include <fstream>
#include "RW.h"
#include "Customer.h"

template<class T>
void writeToFile(const std::vector<T *> &v, const char *fname) {
    std::ofstream file(fname, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::string err = "Could not open ";
        err += fname;
        throw std::runtime_error(err);
    }

    for (T *elem : v) {
        file << elem->to_file() << std::endl;
    }
    file.close();
}

template<class T>
std::vector<T *> readSimpleTable(const char *fname) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::string err = "Could not open ";
        err += fname;
        throw std::runtime_error(err);
    }
    std::vector<T *> v;
    std::string line;
    while (std::getline(infile, line)) {
        v.push_back(T::from_file(line));
    }
    return v;
}


void RW::write(unsigned long id, const std::vector<Plane *> &planes, const std::vector<Employee *> &employees,
               const std::vector<Customer *> &customers, const std::vector<Flight *> &flights,
               const std::vector<Reservation *> &reservations) {
    writeID(id, FILE_ID);
    writeToFile(planes, FILE_PLANE);
    writeToFile(employees, FILE_EMP);
    writeToFile(customers, FILE_CUSTOMER);
    writeToFile(flights, FILE_FLIGHT);
    writeToFile(reservations, FILE_RES);
    writeAssignments(flights, FILE_ASSIGN);
}

DataFile RW::read() {
    DataFile d;
    d.id = readID(FILE_ID);
    // since plane, customer and flight are simple objects (from_file returns themselves, not a tuple),
    // its reading function will look the same - then we use a template function.
    d.planes = readSimpleTable<Plane>(FILE_PLANE);
    d.customers = readSimpleTable<Customer>(FILE_CUSTOMER);
    d.flights = readSimpleTable<Flight>(FILE_FLIGHT);

    // now to the more complicated tables
    d.employees = readEmployees(FILE_EMP);
    d.reservations = readReservations(FILE_RES, d.customers, d.flights);
    readAssignments(FILE_ASSIGN, d.flights, d.employees);
    return d;
}


void RW::writeID(unsigned long id, const char *fname) {
    std::ofstream file(fname, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::string err = "Could not open ";
        err += fname;
        throw std::runtime_error(err);
    }
    file << id;
    file.close();
}

void RW::writeAssignments(const std::vector<Flight *> &flights, const char *fname) {
    std::ofstream file(fname, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::string err = "Could not open ";
        err += fname;
        throw std::runtime_error(err);
    }

    for (Flight *f : flights) {
        std::list<Employee *> crew = f->getAssignedCrew();
        for (Employee *e : crew) {
            file << f->getID() << SEP << e->getID() << std::endl;
        }
    }
    file.close();
}

unsigned long RW::readID(const char *fname) {
    std::ifstream infile(fname);
    std::string line;
    std::getline(infile, line);
    return std::stoul(line);
}

std::vector<Employee *> RW::readEmployees(const char *fname) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::string err = "Could not open ";
        err += fname;
        throw std::runtime_error(err);
    }

    std::vector<Employee *> v;
    std::map<Employee *, std::string> employers;
    std::string line;
    while (std::getline(infile, line)) {
        Employee *e;
        std::string employerID;
        std::tie(e, employerID) = Employee::from_file(line);
        v.push_back(e);
        if (employerID.length() > 0) {
            employers[e] = employerID;
        }
    }

    // now - connect between employee and employer.
    for (auto &kv:employers) {
        Employee *e = kv.first;
        std::string employerID = kv.second;
        for (Employee *potentialEmployer : v) {
            if (potentialEmployer->getID() == employerID) {
                e->setEmployer(potentialEmployer);
                break;
            }
        }
    }
    return v;
}

std::vector<Reservation *> RW::readReservations(const char *fname,
                                                std::vector<Customer *> &customers,
                                                std::vector<Flight *> &flights) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::string err = "Could not open ";
        err += fname;
        throw std::runtime_error(err);
    }

    std::vector<Reservation *> reservations;
    std::string line;
    while (std::getline(infile, line)) {
        Reservation *r;
        std::string customerID;
        std::string flightID;
        std::tie(r, customerID, flightID) = Reservation::from_file(line);

        Customer *c = nullptr;
        Flight *f = nullptr;
        for (Customer *s : customers) {
            if (s->getID() == customerID) {
                c = s;
                break;
            }
        }
        for (Flight *s : flights) {
            if (s->getID() == flightID) {
                f = s;
                break;
            }
        }
        if (!c || !f) {
            throw std::runtime_error("cant find flight or customer of reservation");
        }

        r->setCustomer(c);
        r->setFlight(f);
        c->addReservation(r);
        f->addReservation(r);
        reservations.push_back(r);
    }
    return reservations;
}

void RW::readAssignments(const char *fname, std::vector<Flight *> &flights, const std::vector<Employee *> &employees) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::string err = "Could not open ";
        err += fname;
        throw std::runtime_error(err);
    }

    std::string line;
    while (std::getline(infile, line)) {
        auto tokens = split(line, SEP);
        if (tokens.size() != 2) {
            throw std::runtime_error("bad assignment line");
        }
        std::string flightID = tokens[0];
        std::string employeeID = tokens[1];
        // assignment: flightID, empID

        Flight *f = nullptr;
        Employee *e = nullptr;
        for (Employee *s : employees) {
            if (s->getID() == employeeID) {
                e = s;
                break;
            }
        }
        for (Flight *s : flights) {
            if (s->getID() == flightID) {
                f = s;
                break;
            }
        }
        if (!e || !f) {
            throw std::runtime_error("could not find flight or employee of assignment");
        }

        f->addCrewMember(e);
    }
}


std::vector<std::string> RW::split(const std::string &tosplit, char sep) {
    std::vector<std::string> v;
    std::istringstream iss(tosplit);
    std::string tok;
    while (std::getline(iss, tok, sep)) {
        v.push_back(tok);
    }
    return std::move(v);
}
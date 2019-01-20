//
// Created by sharon_i4 on 26/11/2018.
//

#include <set>
#include <algorithm>
#include "MyImplementation.h"
#include "RW.h"

MyImplementation::MyImplementation() {
    _curr_id = 0;

    try{
        DataFile df = RW::read();
        this->_curr_id = df.id;
        this->_planes = df.planes;
        this->_employees = df.employees;
        this->_customers = df.customers;
        this->_flights = df.flights;
        this->_reservations = df.reservations;
    }catch(...){
        std::cerr << "Could not read from file. continuing as usual..." << std::endl;
    }
}

/**
 * returns a unique id
 * @return
 */

string MyImplementation::getCurrID() {
    return std::to_string(++_curr_id);
}

Employee *MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    string id = getCurrID(); // get a new ID for the new employee we are about to add (it will be different always(
    Employee *e = new Employee(id, title, birth_year, seniority, getEmployee(employer_id)); // create a employee object
    _employees.push_back(e); // add the employee to our employees list
    return e; // return the new created employee
}

Employee *MyImplementation::getEmployee(string id) {
    // search for the employee in our list by comparing the id
    for (Employee *e : _employees) {
        // compare the received id to the current employee ID
        if (id == e->getID()) {
            return e; // if found - return the employee
        }
    }
    // not found - return null
    return nullptr;
}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    string id = getCurrID();
    Plane *p = new Plane(id, model_number, max_passangers[FIRST_CLASS], max_passangers[SECOND_CLASS], crew_needed);
    _planes.push_back(p);
    return p;
}

Plane *MyImplementation::getPlane(string id) {
    for (Plane *p : _planes) {
        if (id == p->getID()) {
            return p;
        }
    }
    return nullptr;
}


std::vector<Plane *> MyImplementation::getPlaneByModel(int modelNum) {
    std::vector<Plane*> planes;
    for (Plane *p : _planes) {
        if (p->getModelNumber() == modelNum) {
            planes.push_back(p);
        }
    }
    return planes;
}

//i Add include to resvation to this file
Flight *MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    // check if a plane with the requested model number exists.
    auto p = getPlaneByModel(model_number);
    // if it does not exist - throw exception.
    if (p.empty()) throw invalid_argument("addflight: no matching plane found");

    // if we got here - we already found a matching plane.
    // now - check if that plane is not occupied in the required date.
    // TODO : well, we dont quite have a way to check it right now through the plane itself
    // TODO: - there is no connection between date and planes inside the plane object.
    // maybe through flights. yes. flights have a model number and a date.
    // therefore - we need to check, if there is another flight who uses the same plane at the same date.
    int numOfFlights = 0;
    for (Flight *f : _flights) {
        if (model_number != f->getModelNumber()) continue;
        // we got here - same model number. now check the date.
        if (f->getDate() == date) {
            ++numOfFlights;
            // then the flight uses the same plane in the same date - we can not use that plane.
        }
    }
    if(numOfFlights >= p.size()){
        // we need to throw an exception - because we can not use that plane model (all occupied)
        throw std::invalid_argument("addFlight: all planes of that model already occupied in that date");
    }
    // if we got here - there is no other flight that uses that plane at the same time - therefore its an available plane.
    // now - check if the crew is available at that date.
    // problem - we need to find a crew. crew is bunch of employees, and employees dont save any reservations.
    // we have no direct connection between crew and dates.
    // the only way to check - is through assigned crew at other flights.
    //
    // logic i suggest - start with a list of all potential crew members.
    // then - remove from that list all the occupied crew members in that date.
    // then - after we got a filtered list of the potential crew, we check if they fulfill the requirement
    // of the plane.
    // if it does not - then we throw exception.
    // if it does - we need to assign that crew to the flight, so in the next searches we will know
    // which employer is occupied
    //
    // IMPLEMENTATION:
    //

    // SUGGESTION - TL:DR I did not do this approach. but i leave the comment.
    // take the opposite approach - instead of filtering, start from the bottom
    // add the employers that are not occupied, instead of removing occupied from full list.
    // problem - this approach is worse in complexity, because to evaluate if a crew member is occupied
    // we need to iterate on all of the flights of that day. which is a problem.
    // REMINDER: THIS LOGIC IS NOT USED. THE FILTER LOGIC IS THE ONE THAT IS USED

    std::vector<Employee *> potentialCrew = _employees; // copy to the set all the employees.

    // remove all occupied crew members. how to know if a crew member is occupied?
    // check in other flights in that date
    for (Flight *f:_flights) {
        if (!(f->getDate() == date)) continue; // if its not the same date- move on
        // all the employees that are occupied // call me
        list<Employee *> assignedCrew = f->getAssignedCrew();
        // filter them out from potential employees.
        potentialCrew.erase(std::remove_if(potentialCrew.begin(), potentialCrew.end(),
                                           [assignedCrew](Employee *e) {
                                               return std::find(assignedCrew.begin(), assignedCrew.end(), e) !=
                                                      assignedCrew.end();
                                           }));
    }
    // we have filtered all the employees that can not work in that day.
    // now - check if there are enough employees for that plane.
    map<Jobs, int> requirements = p[0]->getCrewNeeded(); // this is the map that maps from crew type to number of peopel eneded.

    // now count if we have enough, and save those who are compatible.
    // how ?  i suggest another algorithm
    // iterate on the employees. every time we find a suitible one - decrease its job from the requirements.
    // at the end - the requirements should be all zeroed out.
    vector<Employee *> crew; // the crew that we will use
    for (Employee *e : potentialCrew) {
        Jobs j = e->getTitle();
        // if the job exists in the requirements
        if (requirements.count(j)) {
            // check if the job count is above 0.
            if (requirements[j] > 0) {
                // if it is, then we assign the employeem and decrease the requirements count as we filled a requirement
                requirements[j] = requirements[j] - 1;
                crew.push_back(e);
                continue;
            }
        }
    }
    // now map should be all zeroed out - if its not throw exception
    for (const auto &any : requirements) {
        if (any.second > 0) {
            throw std::logic_error("add flight: not enough available crew members");
        }
    }
    // if we got here - we filled all teh requirements, and we have a vector which contains
    // the crew - then we need to assign them.
    // first - create the flight
    string id = getCurrID(); // unique id
    Flight *f = new Flight(id, model_number, date, source, destination);

    // now - assign all the crew into that flight
    for (Employee *e : crew) {
        f->addCrewMember(e);
    }
    // add the flight to the flight list
    _flights.push_back(f);
    return f;
}

Flight *MyImplementation::getFlight(string id) {
    for (Flight *p: _flights) {
        if (id == p->getID()) {
            return p;
        }
    }
    return nullptr;
}

Customer *MyImplementation::addCustomer(string full_name, int priority) {
    string id = getCurrID();
    if(priority < 1 || priority > 5){
        throw std::runtime_error("Bad Priority");
    }
    Customer *p = new Customer(id, full_name, priority);
    _customers.push_back(p);
    return p;
}

Customer *MyImplementation::getCustomer(string id) {
    for (Customer *p: _customers) {
        if (id == p->getID()) {
            return p;
        }
    }
    return nullptr;
}


Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    Customer *c = getCustomer(customerId);
    if (!c) throw std::invalid_argument("add reservation: no matching customer found");

    Flight *f = getFlight(flightId);
    if (!f) throw std::invalid_argument("add reservation: no matching flight found");

    Plane *p = getPlaneByModel(f->getModelNumber())[0];
    // check if there is enough space
    std::map<Classes, int> availablePlaces;
    availablePlaces[FIRST_CLASS] = p->getMaxFirstClass();
    availablePlaces[SECOND_CLASS] = p->getMaxEconomyClass();
    // now - for every reservation, we will decrease the available place.
    // if for the current class we have no place - we throw exception
    auto existingReservations = f->getReservations();
    for (Reservation *r : existingReservations) {
        availablePlaces[r->getClass()] = availablePlaces[r->getClass()] - 1; // -- might work,did not check that out.
    }

    // if there are no available places for our class - then we fucked up
    if (availablePlaces[cls] <= 0) {
        throw std::invalid_argument("addReservation: not enough reservations in the plane of the flight");
    }

    // now create the reservation
    string id = getCurrID();
    Reservation *r = new Reservation(id, c, f, cls, max_baggage);
    f->addReservation(r); // add the reservation to the flight - so next iteration we will consider the current one.
    _reservations.push_back(r); // save in our list.
    return r;
}

Reservation *MyImplementation::getReservation(string id) {
    for (Reservation *r : _reservations) {
        if (id == r->getID()) {
            return r;
        }
    }
    return nullptr;
}


void MyImplementation::exit() {
    RW::write(_curr_id, _planes, _employees, _customers, _flights, _reservations);
}
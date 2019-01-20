
#ifndef AP1_EMPLOYEE_H
#define AP1_EMPLOYEE_H

#include "ID.h"
#include "Jobs.h"

class Employee : public ID{
public:
    Employee(std::string id, Jobs title, int birthYear, int seniority, Employee *employer);
    ~Employee();

    Jobs getTitle();
    int getBirthYear();
    int getSeniority();
    Employee *getEmployer();
    void setEmployer(Employee *e);

    std::string to_file();
    static std::tuple<Employee*, std::string> from_file(const std::string &line);


private:
    Jobs _title;
    int _birthYear;
    int _seniority;
    Employee *_employer;
};


#endif //AP1_EMPLOYEE_H

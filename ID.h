#ifndef AP1_HASID_H
#define AP1_HASID_H


#include <string>

class ID {
public:
    ID(std::string id) : _id{id} {}

    std::string getID() {
        return _id;
    }

private:
    std::string _id;// stam praivte varbile
};


#endif //AP1_HASID_H

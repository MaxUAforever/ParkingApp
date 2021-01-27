#ifndef Staff_hpp
#define Staff_hpp

#include <stdio.h>
#include <string>

#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{

class Staff
{
public:
    explicit Staff(std::string name);

    EntryKeyID getAccessCode();

private:
    EntryKeyID _accessCode;
    std::string _name;
};

}

#endif /* Staff_hpp */

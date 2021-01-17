#ifndef Ticket_hpp
#define Ticket_hpp

#include <stdio.h>

#include "Car.hpp"
#include "ParkingPlace.hpp"

namespace ParkingEngine
{

class Ticket
{
public:
    Ticket(Car car, ParkingPlace parkingPlace, int startTime);

    const Car& getCar() const;
    const ParkingPlace& getPlace() const;
    const int getStartTime() const;

    bool operator== (const Ticket& ticket) const;
    
private:
    Car _car;
    ParkingPlace _parkingPlace;
    int _startTime;
};

} // namespace ParkingEngine

#endif /* Ticket_hpp */

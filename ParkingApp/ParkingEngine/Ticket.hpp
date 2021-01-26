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
    Ticket(CarRegNumber carRegNumber, PlaceNumber placeNumber, size_t startTime);

    CarRegNumber getCarRegNumber() const;
    PlaceNumber getPlaceNumber() const;
    size_t getStartTime() const;

    bool operator== (const Ticket& ticket) const;
    
private:
    CarRegNumber _carRegNumber;
    PlaceNumber _placeNumber;
    size_t _startTime;
};

} // namespace ParkingEngine

#endif /* Ticket_hpp */

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
    Ticket(CarRegNumber carRegNumber, PlaceIndex placeIndex, size_t startTime);

    CarRegNumber getCarRegNumber() const;
    PlaceIndex getPlaceIndex() const;
    size_t getStartTime() const;

    bool operator== (const Ticket& ticket) const;
    
private:
    CarRegNumber _carRegNumber;
    PlaceIndex _placeIndex;
    size_t _startTime;
};

} // namespace ParkingEngine

#endif /* Ticket_hpp */

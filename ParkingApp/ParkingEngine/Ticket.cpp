#include "Ticket.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

Ticket::Ticket(CarRegNumber carRegNumber, PlaceNumber placeNumber, size_t startTime)
    : _carRegNumber(carRegNumber)
    , _placeNumber(placeNumber)
    , _startTime(startTime)
{}

CarRegNumber Ticket::getCarRegNumber() const
{
    return _carRegNumber;
}

PlaceNumber Ticket::getPlaceNumber() const
{
    return _placeNumber;
}

size_t Ticket::getStartTime() const
{
    return _startTime;
}

bool Ticket::operator== (const Ticket& ticket) const
{
    return std::tie(_startTime, _placeNumber, _carRegNumber) ==
           std::tie(ticket._startTime, ticket._placeNumber, ticket._carRegNumber);
}

} // namespace ParkingEngine

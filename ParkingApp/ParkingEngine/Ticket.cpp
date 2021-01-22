#include "Ticket.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

Ticket::Ticket(CarRegNumber carRegNumber, PlaceIndex placeIndex, size_t startTime)
    : _carRegNumber(carRegNumber)
    , _placeIndex(placeIndex)
    , _startTime(startTime)
{}

CarRegNumber Ticket::getCarRegNumber() const
{
    return _carRegNumber;
}

PlaceIndex Ticket::getPlaceIndex() const
{
    return _placeIndex;
}

size_t Ticket::getStartTime() const
{
    return _startTime;
}

bool Ticket::operator== (const Ticket& ticket) const
{
    return std::tie(_startTime, _placeIndex, _carRegNumber) ==
           std::tie(ticket._startTime, ticket._placeIndex, ticket._carRegNumber);
}

} // namespace ParkingEngine

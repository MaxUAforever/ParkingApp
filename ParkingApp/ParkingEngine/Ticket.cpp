#include "Ticket.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

Ticket::Ticket(Car car, ParkingPlace parkingPlace, int startTime)
    : _car(std::move(car))
    , _parkingPlace(std::move(parkingPlace))
    , _startTime(startTime)
{}

const Car& Ticket::getCar() const
{
    return _car;
}

const ParkingPlace& Ticket::getPlace() const
{
    return _parkingPlace;
}

const int Ticket::getStartTime() const
{
    return _startTime;
}

bool Ticket::operator== (const Ticket& ticket) const
{
    return std::tie(_startTime, _parkingPlace, _car) ==
           std::tie(ticket._startTime, ticket._parkingPlace, ticket._car);
}

} // namespace ParkingEngine

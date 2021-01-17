#include <cassert>

#include "Parking.hpp"

namespace ParkingEngine
{

Parking::Parking(size_t placesCount, size_t barriersCount)
{
    _freePlaces.reserve(placesCount);
    for (auto i = 0; i < placesCount; ++i)
    {
        _freePlaces.emplace_back(i + 1);
    }
}

bool Parking::acceptCar(const Car& car, int barrierNumber)
{
    if (_freePlaces.empty())
    {
        return false;
    }
    
    // auto ticket = _barriers[barrier].getTicket(car, 0);
    auto ticket = Ticket(car, _freePlaces.back(), 0);
    _tickets.insert({car.getRegNumber(), std::move(ticket)});
    _freePlaces.pop_back();
    
    return true;
}

void Parking::releaseCar(const Car& car, int barrierNumber)
{
    auto ticketIt = _tickets.find(car.getRegNumber());
    if (ticketIt != _tickets.end())
    {
        _tickets.erase(ticketIt);
    }
}

} // namespace ParkingEngine

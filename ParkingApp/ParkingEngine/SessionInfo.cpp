#include "SessionInfo.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

SessionInfo::SessionInfo(CarRegNumber carRegNumber, PlaceNumber placeNumber, size_t startTime)
    : _carRegNumber(carRegNumber)
    , _placeNumber(placeNumber)
    , _startTime(startTime)
{}

CarRegNumber SessionInfo::getCarRegNumber() const
{
    return _carRegNumber;
}

PlaceNumber SessionInfo::getPlaceNumber() const
{
    return _placeNumber;
}

size_t SessionInfo::getStartTime() const
{
    return _startTime;
}

bool SessionInfo::operator== (const SessionInfo& ticket) const
{
    return std::tie(_startTime, _placeNumber, _carRegNumber) ==
           std::tie(ticket._startTime, ticket._placeNumber, ticket._carRegNumber);
}

} // namespace ParkingEngine

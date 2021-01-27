#include "SessionInfo.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

SessionInfo::SessionInfo(VehicleRegNumber carRegNumber, PlaceNumber placeNumber, size_t startTime)
    : _carRegNumber(carRegNumber)
    , _placeNumber(placeNumber)
    , _startTime(startTime)
{}

VehicleRegNumber SessionInfo::getVehicleRegNumber() const
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

bool SessionInfo::operator== (const SessionInfo& session) const
{
    return std::tie(_startTime, _placeNumber, _carRegNumber) ==
           std::tie(session._startTime, session._placeNumber, session._carRegNumber);
}

} // namespace ParkingEngine

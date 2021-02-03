#include "SessionInfo.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

SessionInfo::SessionInfo(EntryKeyID keyID, VehicleRegNumber carRegNumber, PlaceNumber placeNumber, size_t startTime)
    : _keyID(keyID)
    , _carRegNumber(carRegNumber)
    , _placeNumber(placeNumber)
    , _startTime(startTime)
{}

EntryKeyID SessionInfo::getKeyID() const
{
    return _keyID;
}

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

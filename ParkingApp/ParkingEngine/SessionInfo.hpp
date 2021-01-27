#ifndef SessionInfo_hpp
#define SessionInfo_hpp

#include <stdio.h>

#include "Vehicle.hpp"
#include "ParkingPlace.hpp"

namespace ParkingEngine
{

class SessionInfo
{
public:
    SessionInfo(VehicleRegNumber carRegNumber, PlaceNumber placeNumber, size_t startTime);

    VehicleRegNumber getVehicleRegNumber() const;
    PlaceNumber getPlaceNumber() const;
    size_t getStartTime() const;

    bool operator== (const SessionInfo& session) const;
    
private:
    VehicleRegNumber _carRegNumber;
    PlaceNumber _placeNumber;
    size_t _startTime;
};

} // namespace ParkingEngine

#endif /* SessionInfo_hpp */

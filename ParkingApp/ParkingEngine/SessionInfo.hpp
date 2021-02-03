#ifndef SessionInfo_hpp
#define SessionInfo_hpp

#include <stdio.h>

#include "Vehicle.hpp"
#include "ParkingPlace.hpp"
#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{

class SessionInfo
{
public:
    SessionInfo(EntryKeyID keyID, VehicleRegNumber carRegNumber, PlaceNumber placeNumber, size_t startTime);

    EntryKeyID getKeyID() const;
    VehicleRegNumber getVehicleRegNumber() const;
    PlaceNumber getPlaceNumber() const;
    size_t getStartTime() const;

    bool operator== (const SessionInfo& session) const;
    
private:
    EntryKeyID _keyID;
    VehicleRegNumber _carRegNumber;
    PlaceNumber _placeNumber;
    size_t _startTime;
};

} // namespace ParkingEngine

#endif /* SessionInfo_hpp */

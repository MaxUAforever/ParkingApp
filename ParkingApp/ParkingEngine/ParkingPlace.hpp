#ifndef ParkingPlace_hpp
#define ParkingPlace_hpp

#include "Vehicle.hpp"

#include <cstdint>
#include <stdio.h>

namespace ParkingEngine
{
using PlaceID = size_t;

class ParkingPlace
{
public:
    explicit ParkingPlace(PlaceID placeID, size_t number = 0, int floor = 0, bool isForDisabledPerson = false, VehicleType vehicleType = VehicleType::Car);
    
    PlaceID getPlaceID() const;
    void setPlaceID(PlaceID placeID);
    
    size_t getPlaceNumber() const;
    void setPlaceNumber(size_t number);
    
    int getFloor() const;
    void setFloor(int floor);
    
    bool isForDisabledPerson() const;
    void setIsForDisabledPerson(bool isForDisabledPerson);
    
    VehicleType getVehicleType() const;
    void setVehicleType(VehicleType vehicleType);
    
    bool operator== (const ParkingPlace& place) const;
    bool operator< (const ParkingPlace& place) const;
    
private:
    PlaceID _placeID;
    size_t _number;
    VehicleType _vehicleType;
    bool _isForDisabledPerson;
    int _floor;
};

} // namespace ParkingEngine

#endif /* ParkingPlace_hpp */

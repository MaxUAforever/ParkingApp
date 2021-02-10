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
    explicit ParkingPlace(PlaceID number, int floor = 0, bool isForDisabledPerson = false, VehicleType vehicleType = VehicleType::Car);
    
    PlaceID getNumber() const;
    void setNumber(PlaceID number);
    
    int getFloor() const;
    void setFloor(int floor);
    
    bool isForDisabledPerson() const;
    void setIsForDisabledPerson(bool isForDisabledPerson);
    
    VehicleType getVehicleType() const;
    void setVehicleType(VehicleType vehicleType);
    
    bool operator== (const ParkingPlace& place) const;
    bool operator< (const ParkingPlace& place) const;
    
private:
    PlaceID _number;
    VehicleType _vehicleType;
    bool _isForDisabledPerson;
    int _floor;
};

} // namespace ParkingEngine

#endif /* ParkingPlace_hpp */

#ifndef ParkingPlace_hpp
#define ParkingPlace_hpp

#include "Vehicle.hpp"

#include <cstdint>
#include <stdio.h>

namespace ParkingEngine
{
using PlaceNumber = size_t;

class ParkingPlace
{
public:
    explicit ParkingPlace(PlaceNumber number, int floor = 0, bool isForDisabledPerson = false, VehicleType vehicleType = VehicleType::Car);
    
    PlaceNumber getNumber() const;
    void setNumber(PlaceNumber number);
    
    int getFloor() const;
    void setFloor(int floor);
    
    bool isForDisabledPerson() const;
    void setIsForDisabledPerson(bool isForDisabledPerson);
    
    VehicleType getVehicleType() const;
    void setVehicleType(VehicleType vehicleType);
    
    bool operator== (const ParkingPlace& place) const;
    bool operator< (const ParkingPlace& place) const;
    
private:
    PlaceNumber _number;
    VehicleType _vehicleType;
    bool _isForDisabledPerson;
    int _floor;
};

} // namespace ParkingEngine

#endif /* ParkingPlace_hpp */

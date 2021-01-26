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
    explicit ParkingPlace(PlaceNumber number, int floor = 1, bool isForDisabled = false, VehicleType vehicleType = VehicleType::Car);
    
    PlaceNumber getNumber() const;
    void setNumber(PlaceNumber number);
    
    int getFloor() const;
    void setFloor(int floor);
    
    bool isForDisabled() const;
    void setIsForDisabled(bool isForDisabled);
    
    VehicleType getVehicleType() const;
    void setVehicleType(VehicleType vehicleType);
    
    bool operator== (const ParkingPlace& place) const;
    bool operator< (const ParkingPlace& place) const;
    
private:
    PlaceNumber _number;
    int _floor;
    bool _isForDisabled;
    VehicleType _vehicleType;
};

} // namespace ParkingEngine

#endif /* ParkingPlace_hpp */

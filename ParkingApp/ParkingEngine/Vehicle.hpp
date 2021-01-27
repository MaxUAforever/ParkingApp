#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include <iostream>
#include <string>

namespace ParkingEngine
{
using VehicleRegNumber = std::string;

enum class VehicleType : std::uint8_t
{
    Car,
    Truck,
    Motorbyke
};

class Vehicle
{
public:
    explicit Vehicle(VehicleRegNumber regNumber, VehicleType type);
    
    VehicleRegNumber getRegNumber() const;
    VehicleType getType() const;
    
    bool operator== (const Vehicle& vehicle) const;
    
private:
    VehicleRegNumber _regNumber;
    VehicleType _type;
};

} // namespace ParkingEngine

#endif /* Vehicle_hpp */

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <stdio.h>
#include <iostream>

namespace ParkingEngine
{
using CarRegNumber = int;

enum class VehicleType : std::uint8_t
{
    Car,
    Truck,
    Motorbyke
};

class Vehicle
{
public:
    explicit Vehicle(int regNumber, VehicleType type);
    
    const CarRegNumber getRegNumber() const;
    
    bool operator== (const Vehicle& vehicle) const;
    
private:
    CarRegNumber _regNumber;
    VehicleType _type;
};

} // namespace ParkingEngine

#endif /* Vehicle_hpp */

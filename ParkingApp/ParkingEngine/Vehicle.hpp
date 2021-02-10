#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <boost/optional.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

namespace ParkingEngine
{
using VehicleRegNumber = std::string;
using VehicleRegNumberOpt =  boost::optional<VehicleRegNumber>;

enum class VehicleType : std::uint8_t
{
    Bicycle,
    Car,
    Truck,
    Motorbyke
};

class Vehicle
{
public:
    explicit Vehicle(VehicleType type, VehicleRegNumberOpt regNumber = boost::none);
    
    VehicleType getType() const;
    
    VehicleRegNumberOpt getRegNumber() const;
    void setRegNumber(VehicleRegNumber regNmber);
    
    bool operator== (const Vehicle& vehicle) const;
    
private:
    VehicleType _type;
    VehicleRegNumberOpt _regNumber;
};

} // namespace ParkingEngine

#endif /* Vehicle_hpp */

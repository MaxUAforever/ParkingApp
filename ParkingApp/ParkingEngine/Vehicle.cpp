#include "Vehicle.hpp"

namespace ParkingEngine
{

Vehicle::Vehicle(int regNumber, VehicleType type)
    : _regNumber(regNumber)
    , _type(type)
{
}
    
const CarRegNumber Vehicle::getRegNumber() const
{
    return _regNumber;
}

bool Vehicle::operator== (const Vehicle& vehicle) const
{
    return _regNumber == vehicle._regNumber;
}

} // namespace ParkingEngine

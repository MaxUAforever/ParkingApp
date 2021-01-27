#include "Vehicle.hpp"

namespace ParkingEngine
{

Vehicle::Vehicle(VehicleRegNumber regNumber, VehicleType type)
    : _regNumber(regNumber)
    , _type(type)
{
}

VehicleRegNumber Vehicle::getRegNumber() const
{
    return _regNumber;
}

VehicleType Vehicle::getType() const
{
    return _type;
}

bool Vehicle::operator== (const Vehicle& vehicle) const
{
    return _regNumber == vehicle._regNumber;
}

} // namespace ParkingEngine

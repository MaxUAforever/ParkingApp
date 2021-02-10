#include "Vehicle.hpp"

namespace ParkingEngine
{

Vehicle::Vehicle(VehicleType type, VehicleRegNumberOpt regNumber)
    : _type(type)
    , _regNumber(regNumber)
{
}

VehicleRegNumberOpt Vehicle::getRegNumber() const
{
    return _regNumber;
}

void Vehicle::setRegNumber(VehicleRegNumber regNumber)
{
    _regNumber = regNumber;
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

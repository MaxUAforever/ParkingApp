#include "ParkingPlace.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

ParkingPlace::ParkingPlace(size_t number, int floor, bool isForDisabledPerson, VehicleType vehicleType)
    : _number(number)
    , _floor(floor)
    , _isForDisabledPerson(isForDisabledPerson)
    , _vehicleType(vehicleType)
{}
    
PlaceNumber ParkingPlace::getNumber() const
{
    return _number;
}

void ParkingPlace::setNumber(PlaceNumber number)
{
    _number = number;
}

int ParkingPlace::getFloor() const
{
    return _floor;
}

void ParkingPlace::setFloor(int floor)
{
    _floor = floor;
}

bool ParkingPlace::isForDisabledPerson() const
{
    return _isForDisabledPerson;
}

void ParkingPlace::setIsForDisabledPerson(bool isForDisabledPerson)
{
    _isForDisabledPerson = isForDisabledPerson;
}

VehicleType ParkingPlace::getVehicleType() const
{
    return _vehicleType;
}

void ParkingPlace::setVehicleType(VehicleType vehicleType)
{
    _vehicleType = vehicleType;
}

bool ParkingPlace::operator== (const ParkingPlace& place) const
{
    return std::tie(_number, _floor, _isForDisabledPerson, _vehicleType) ==
           std::tie(place._number, place._floor, place._isForDisabledPerson, place._vehicleType);
}

bool ParkingPlace::operator< (const ParkingPlace& place) const
{
    return _number < place._number;
}

} // namespace ParkingEngine

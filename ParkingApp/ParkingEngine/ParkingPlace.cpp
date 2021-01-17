#include "ParkingPlace.hpp"

namespace ParkingEngine
{

ParkingPlace::ParkingPlace(size_t number)
    : _number(number)
{
}
    
const size_t ParkingPlace::getNumber() const
{
    return _number;
}

bool ParkingPlace::operator== (const ParkingPlace& place) const
{
    return _number == place._number;
}

} // namespace ParkingEngine

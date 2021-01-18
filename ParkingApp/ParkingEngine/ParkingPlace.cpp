#include "ParkingPlace.hpp"

namespace ParkingEngine
{

ParkingPlace::ParkingPlace(PlaceIndex number)
    : _number(number)
    , _price(100)
{
}
    
const PlaceIndex ParkingPlace::getNumber() const
{
    return _number;
}

const size_t ParkingPlace::getPrice() const
{
    return _price;
}

bool ParkingPlace::operator== (const ParkingPlace& place) const
{
    return _number == place._number;
}

bool ParkingPlace::operator< (const ParkingPlace& place) const
{
    return _number < place._number;
}

} // namespace ParkingEngine

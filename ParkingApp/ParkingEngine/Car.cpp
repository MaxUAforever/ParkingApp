#include "Car.hpp"

namespace ParkingEngine
{

Car::Car(int regNumber)
    : _regNumber(regNumber)
{
}
    
const CarRegNumber Car::getRegNumber() const
{
    return _regNumber;
}

bool Car::operator== (const Car& car) const
{
    return _regNumber == car._regNumber;
}

} // namespace ParkingEngine

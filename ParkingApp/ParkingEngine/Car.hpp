#ifndef Car_hpp
#define Car_hpp

#include <stdio.h>
#include <iostream>

namespace ParkingEngine
{
using CarRegNumber = int;

class Car
{
public:
    explicit Car(int regNumber);
    
    const CarRegNumber getRegNumber() const;
    
    bool operator== (const Car& car) const;
    
private:
    CarRegNumber _regNumber;
};

} // namespace ParkingEngine

#endif /* Car_hpp */

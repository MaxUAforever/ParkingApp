#ifndef Parking_hpp
#define Parking_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>

#include "Car.hpp"
#include "ParkingPlace.hpp"
#include "Ticket.hpp"

namespace ParkingEngine
{

class Parking
{
public:
    Parking(size_t placesCount, size_t barriersCount);

    bool acceptCar(const Car& car, int barrierNumber);
    void releaseCar(const Car& car, int barrierNumber);

private:
    std::vector<ParkingPlace> _freePlaces;
    std::unordered_map<CarRegNumber, Ticket> _tickets;
};

} //namespace ParkingEngine

#endif /* Parking_hpp */

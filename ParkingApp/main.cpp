#include <iostream>

#include "ParkingEngine/Car.hpp"
#include "ParkingEngine/Parking.hpp"
#include "ParkingEngine/Ticket.hpp"

using namespace ParkingEngine;

void processParkingAccessResult(const AccessResult& result)
{
    if (result.type() == typeid(AccessErrorCode))
    {
        const auto errorCode = boost::get<AccessErrorCode>(result);
        
        switch (errorCode) {
            case AccessErrorCode::NotEmptyPlace:
            {
                std::cout << "Sorry, this place isn't free.\n";
                break;
            }
            case AccessErrorCode::DuplicateCarNumber:
            {
                std::cout << "This car is already parked!.\n";
                break;
            }
            case AccessErrorCode::FullParking:
            {
                std::cout << "Sorry, parking is full.\n";
                break;
            }
        }
    }
    else if (result.type() == typeid(Ticket))
    {
        const auto ticket = boost::get<Ticket>(result);
        std::cout << "Welcome! Your place is " << ticket.getPlace().getNumber() << ".\n";
    }
}

void printFreePlaces(const Parking& parking)
{
    std::cout << "Free places: ";
    for (const auto& placeIndex : parking.getFreePlacesList())
    {
        std::cout << placeIndex << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[])
{
    Car car1(1);
    Car car2(2);
    Car car3(3);
    
    Parking parking(2, 1);
    
    printFreePlaces(parking);
    std::cout << std::endl;
    
    std::cout << "Try to push car to the first place:\n";
    processParkingAccessResult(parking.acceptCar(car1, 0));
    std::cout << std::endl;
    
    std::cout << "Try to push the same car:\n";
    processParkingAccessResult(parking.acceptCar(car1, 0));
    std::cout << std::endl;
    
    std::cout << "Try to push second car to not free place:\n";
    processParkingAccessResult(parking.acceptCar(car2, 0, 1));
    std::cout << std::endl;
    
    std::cout << "Try to push second car to free place:\n";
    processParkingAccessResult(parking.acceptCar(car2, 0, 2));
    std::cout << std::endl;
    
    std::cout << "Try to push third car to full parking:\n";
    processParkingAccessResult(parking.acceptCar(car3, 0));
    std::cout << std::endl;
    
    std::cout << "Try to pop second car and push third:\n";
    parking.releaseCar(car2, 0);
    processParkingAccessResult(parking.acceptCar(car3, 0));
    std::cout << std::endl;
    
    return 0;
}

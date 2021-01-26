#include <iostream>

#include "ParkingEngine/Vehicle.hpp"
#include "ParkingEngine/Parking.hpp"
#include "ParkingEngine/SessionInfo.hpp"

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
                std::cout << "This vehicle is already parked!.\n";
                break;
            }
            case AccessErrorCode::FullParking:
            {
                std::cout << "Sorry, parking is full.\n";
                break;
            }
        }
    }
    else if (result.type() == typeid(SessionInfo))
    {
        const auto ticket = boost::get<SessionInfo>(result);
        std::cout << "Welcome! Your place is " << ticket.getPlaceNumber() << ".\n";
    }
}

void printFreePlaces(const Parking& parking)
{
    std::cout << "Free places: ";
    for (const auto& placeNumber : parking.getFreePlacesList())
    {
        std::cout << placeNumber << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[])
{
    Vehicle car1(1, VehicleType::Car);
    Vehicle car2(2, VehicleType::Car);
    Vehicle car3(3, VehicleType::Car);
    
    Parking parking(2, 1);
    
    printFreePlaces(parking);
    std::cout << std::endl;
    
    std::cout << "Try to push vehicle to the first place:\n";
    processParkingAccessResult(parking.acceptCar(car1, 0));
    std::cout << std::endl;
    
    std::cout << "Try to push the same vehicle:\n";
    processParkingAccessResult(parking.acceptCar(car1, 0));
    std::cout << std::endl;
    
    std::cout << "Try to push second vehicle to not free place:\n";
    processParkingAccessResult(parking.acceptCar(car2, 0, 1));
    std::cout << std::endl;
    
    std::cout << "Try to push second vehicle to free place:\n";
    processParkingAccessResult(parking.acceptCar(car2, 0, 2));
    std::cout << std::endl;
    
    std::cout << "Try to push third vehicle to full parking:\n";
    processParkingAccessResult(parking.acceptCar(car3, 0));
    std::cout << std::endl;
    
    std::cout << "Try to pop second vehicle and push third:\n";
    parking.releaseCar(car2, 0);
    processParkingAccessResult(parking.acceptCar(car3, 0));
    std::cout << std::endl;
    
    return 0;
}

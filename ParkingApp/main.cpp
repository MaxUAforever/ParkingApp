#include <iostream>

#include "ParkingEngine/Vehicle.hpp"
#include "ParkingEngine/Parking.hpp"
#include "ParkingEngine/ParkingFactory.hpp"

#include <boost/optional.hpp>

using namespace ParkingEngine;

boost::optional<Ticket> processParkingAccessResult(const AccessResult& result)
{
    if (result.type() == typeid(AccessErrorCode))
    {
        const auto errorCode = boost::get<AccessErrorCode>(result);
        
        switch (errorCode)
        {
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
            case AccessErrorCode::WrongPlaceID:
            {
                std::cout << "Place number is incorrect.\n";
                break;
            }
            case AccessErrorCode::NotDisabledVehicle:
            {
                std::cout << "This place is reserved only for disabled persons.\n";
                break;
            }
            case AccessErrorCode::WrongVehicleType:
            {
                std::cout << "This place is for another vahivle type.\n";
                break;
            }
            case AccessErrorCode::NotAvailableVelRegService:
            {
                std::cout << "Vehicles register service is not responding. Please, call operator.\n";
                break;
            }
            case AccessErrorCode::NotSuccessfulPayment:
            {
                std::cout << "Payment is not successful!\n";
                break;
            }
            case AccessErrorCode::BarrierIsBroken:
            {
                std::cout << "Barrier is broken. Please, wait for operator.\n";
                break;
            }
        }
    }
    else if (result.type() == typeid(Ticket))
    {
        const auto ticket = boost::get<Ticket>(result);
        std::cout << "Welcome! Your place is " << ticket.getPlaceID() << ".\n";
        
        return ticket;
    }
    
    return boost::none;
}

void printFreePlaces(const Parking& parking)
{
    std::cout << "Free places: ";
    for (const auto& placeID : parking.getFreePlacesList())
    {
        std::cout << placeID << " ";
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[])
{
    Vehicle car1(VehicleType::Car, std::string("C065MK"));
    Vehicle car2(VehicleType::Car, std::string("C404OC"));
    Vehicle car3(VehicleType::Car, std::string("A134AA"));
    
    auto parking = ParkingFacory().createParking(5, 2, 100, 0.8, 10);
    
    printFreePlaces(*parking);
    std::cout << std::endl;
    
    std::cout << "Try to push vehicle to the first place:\n";
    processParkingAccessResult(parking->acceptVehicle(car1, 0));
    std::cout << std::endl;
    
    std::cout << "Try to push second vehicle to not free place:\n";
    processParkingAccessResult(parking->acceptVehicle(car2, 0, 1));
    std::cout << std::endl;
    
    std::cout << "Try to push second vehicle to free place:\n";
    auto ticket = processParkingAccessResult(parking->acceptVehicle(car2, 0, 2));
    std::cout << std::endl;
    
    std::cout << "Try to push third vehicle to full parking:\n";
    processParkingAccessResult(parking->acceptVehicle(car3, 0));
    std::cout << std::endl;
    
    std::cout << "Try to pop second vehicle and push third:\n";
    if (ticket)
    {
        parking->releaseVehicle(ticket->getKeyID(), 0);
    }
    
    processParkingAccessResult(parking->acceptVehicle(car3, 0));
    std::cout << std::endl;
    
    return 0;
}

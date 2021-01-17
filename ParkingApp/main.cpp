//
//  main.cpp
//  ParkingApp
//
//  Created by Maxim Tytskiy on 16.01.2021.
//

#include <iostream>

#include "ParkingEngine/Car.hpp"
#include "ParkingEngine/Parking.hpp"

int main(int argc, const char * argv[]) {
    using namespace ParkingEngine;
    
    Car car(1);
    Parking parking(10, 2);
    
    parking.releaseCar(car, 0);
    parking.acceptCar(car, 0);
    parking.releaseCar(car, 0);
    
    std::cout << "Hello, " << car.getRegNumber() << "!\n";
    return 0;
}

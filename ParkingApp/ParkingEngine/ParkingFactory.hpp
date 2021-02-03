#ifndef ParkingFactory_hpp
#define ParkingFactory_hpp

#include <stdio.h>

#include "Parking.hpp"

namespace ParkingEngine
{

class ParkingFacory
{
public:
    static std::unique_ptr<Parking> createParking(size_t barriersCount,
                                                  size_t placesCount,
                                                  double priceBaseСoefficient,
                                                  double disabledPersonDiscountCoef,
                                                  size_t floorDiscount);
};

} // namespace ParkingEngine

#endif /* ParkingFactory_hpp */

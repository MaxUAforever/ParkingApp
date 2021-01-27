#ifndef PaymentManager_hpp
#define PaymentManager_hpp

#include "Vehicle.hpp"

#include <stdio.h>
#include <unordered_map>

namespace ParkingEngine
{
class SessionInfo;
class ParkingPlace;

class PaymentManager
{
public:
    PaymentManager(double priceBaseСoefficient,
                   double disabledPersonDiscountCoef,
                   size_t floorDiscount);
    
    size_t getTotalPrice(const SessionInfo& session, const ParkingPlace& place);
    
    size_t getPriceBaseСoefficient() const;
    void setPriceBaseСoefficient(size_t priceBaseСoefficient);
    
    void setVelicheCoefficient(VehicleType vehicleType, double vehicleCoefficient);
    double getVelicheCoefficient(VehicleType vehicleType) const;
    
private:
    double _priceBaseСoefficient;
    double _disabledPersonDiscountCoef;
    size_t _floorDiscount;
    std::unordered_map<VehicleType, double> _vehicleCoefficients;
};

} // namespace ParkingEngine

#endif /* PaymentManager_hpp */

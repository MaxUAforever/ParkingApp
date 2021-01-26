#include "PaymentManager.hpp"

#include "ParkingPlace.hpp"
#include "Ticket.hpp"
#include "TimeManager.hpp"

#include <cmath>

namespace ParkingEngine
{

PaymentManager::PaymentManager(double priceBaseСoefficient,
                               double disabledPersonDiscountCoef,
                               size_t floorDiscount)
    : _priceBaseСoefficient(priceBaseСoefficient)
    , _disabledPersonDiscountCoef(disabledPersonDiscountCoef)
    , _floorDiscount(floorDiscount)
{}

size_t PaymentManager::getTotalPrice(const Ticket& ticket, const ParkingPlace& place)
{
    const auto durationTime = TimeManager::getCurrentTime() - ticket.getStartTime();
    const auto totalFloorDiscount = (std::abs(place.getFloor()) - 1) * _floorDiscount;
    
    size_t totalPrice = std::round(durationTime * _priceBaseСoefficient * _disabledPersonDiscountCoef - totalFloorDiscount);
    
    return totalPrice;
}

void PaymentManager::setVelicheCoefficient(VehicleType vehicleType, double vehicleCoefficient)
{
    _vehicleCoefficients.emplace(vehicleType, vehicleCoefficient);
}

double PaymentManager::getVelicheCoefficient(VehicleType vehicleType) const
{
    auto coefficientIt = _vehicleCoefficients.find(vehicleType);
    if (coefficientIt != _vehicleCoefficients.end())
    {
        return coefficientIt->second;
    }
    
    return 1;
}

size_t PaymentManager::getPriceBaseСoefficient() const
{
    return _priceBaseСoefficient;
}

void PaymentManager::setPriceBaseСoefficient(size_t priceBaseСoefficient)
{
    _priceBaseСoefficient = priceBaseСoefficient;
}

} // namespace ParkingEngine

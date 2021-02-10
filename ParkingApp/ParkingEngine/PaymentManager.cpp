#include "PaymentManager.hpp"

#include "ParkingPlace.hpp"
#include "TimeManager.hpp"

#include <cmath>

namespace ParkingEngine
{

PaymentManager::PaymentManager(const ITimeManager& timeManager,
                               const IParkingPlacesManager& placesManager,
                               const IStaffManager& staffManager,
                               VehicleDiscounts vehicleDiscounts,
                               double priceBaseСoefficient,
                               double disabledPersonDiscountCoef,
                               size_t floorDiscount)
    : _timeManager(timeManager)
    , _placesManager(placesManager)
    , _staffManager(staffManager)
    , _vehicleCoefficients()
    , _priceBaseСoefficient(priceBaseСoefficient)
    , _disabledPersonDiscountCoef(disabledPersonDiscountCoef)
    , _floorDiscount(floorDiscount)
{
    _paymentService = std::make_unique<PaymentService>();
}

bool PaymentManager::getPayment(EntryKeyID keyID) const
{
    const auto totalPrice = getTotalPrice(keyID);
    
    if (totalPrice && !_paymentService->getPayment(totalPrice))
    {
        return false;
    }
    
    notifyObservers(keyID);
    return true;
}

size_t PaymentManager::getTotalPrice(EntryKeyID keyID) const
{
    const auto& durationTime = _timeManager.getSessionDuraton(keyID);
    const auto& place = _placesManager.getReservedPlace(keyID);
    
    if(_staffManager.getStaff(keyID))
    {
        return 0;
    }
    
    size_t totalPrice = durationTime * _priceBaseСoefficient;
    
    const auto totalFloorDiscount = (std::abs(place->getFloor()) - 1) * _floorDiscount;
    totalPrice -= totalFloorDiscount;
    
    const auto vehicleCoefficient = getVelicheCoefficient(place->getVehicleType());
    totalPrice *= vehicleCoefficient;
    
    return totalPrice;
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

void PaymentManager::registerObserver(IPaymentObserver* observer)
{
    _observers.push_back(observer);
}

void PaymentManager::notifyObservers(EntryKeyID keyID) const
{
    for (auto observer : _observers)
    {        
        observer->onSuccessPayment(keyID);
    }
}

} // namespace ParkingEngine

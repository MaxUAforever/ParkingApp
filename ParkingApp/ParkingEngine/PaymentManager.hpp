#ifndef PaymentManager_hpp
#define PaymentManager_hpp

// TODO: addITimeManager.
#include "IPaymentObserver.h"
#include "TimeManager.hpp"
#include "EntryKeyGenerator.hpp"
#include "IPaymentManager.hpp"
#include "IParkingPlacesManager.hpp"
#include "PaymentService.hpp"
#include "Vehicle.hpp"

#include <unordered_map>
#include <vector>

namespace ParkingEngine
{

class PaymentManager : public IPaymentManager
{
public:
    PaymentManager(const TimeManager& timeManager,
                   const IParkingPlacesManager& placesManager,
                   double priceBaseСoefficient,
                   double disabledPersonDiscountCoef,
                   size_t floorDiscount);
    
    bool getPayment(EntryKeyID keyID) const override;
    size_t getTotalPrice(EntryKeyID keyID) const override;
    
    size_t getPriceBaseСoefficient() const;
    void setPriceBaseСoefficient(size_t priceBaseСoefficient);
    double getVelicheCoefficient(VehicleType vehicleType) const;
    void setVelicheCoefficient(VehicleType vehicleType, double vehicleCoefficient) override;
    
    void registerObserver(IPaymentObserver* observer) override;
    
private:
    void notifyObservers(EntryKeyID keyID) const;
    
private:
    const TimeManager& _timeManager;
    const IParkingPlacesManager& _placesManager;
    std::unique_ptr<PaymentService> _paymentService;
    std::vector<IPaymentObserver*> _observers;

    double _priceBaseСoefficient;
    double _disabledPersonDiscountCoef;
    size_t _floorDiscount;
    std::unordered_map<VehicleType, double> _vehicleCoefficients;
};

} // namespace ParkingEngine

#endif /* PaymentManager_hpp */

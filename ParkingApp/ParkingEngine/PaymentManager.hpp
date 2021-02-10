#ifndef PaymentManager_hpp
#define PaymentManager_hpp

#include "IPaymentObserver.h"
#include "ITimeManager.h"
#include "EntryKeyGenerator.hpp"
#include "IPaymentManager.hpp"
#include "IParkingPlacesManager.hpp"
#include "PaymentService.hpp"
#include "Vehicle.hpp"

#include <unordered_map>
#include <vector>

namespace ParkingEngine
{
using VehicleDiscounts = std::unordered_map<VehicleType, double>;

class PaymentManager : public IPaymentManager
{
public:
    PaymentManager(const ITimeManager& timeManager,
                   const IParkingPlacesManager& placesManager,
                   const VehicleDiscounts vehicleDiscounts,
                   double priceBaseСoefficient,
                   double disabledPersonDiscountCoef,
                   size_t floorDiscount);
    
    bool getPayment(EntryKeyID keyID) const override;
    size_t getTotalPrice(EntryKeyID keyID) const override;
    
    size_t getPriceBaseСoefficient() const;
    double getVelicheCoefficient(VehicleType vehicleType) const;
    
    void registerObserver(IPaymentObserver* observer) override;
    
private:
    void notifyObservers(EntryKeyID keyID) const;
    
private:
    const ITimeManager& _timeManager;
    const IParkingPlacesManager& _placesManager;
    std::unique_ptr<PaymentService> _paymentService;
    std::vector<IPaymentObserver*> _observers;

    double _priceBaseСoefficient;
    double _disabledPersonDiscountCoef;
    size_t _floorDiscount;
    VehicleDiscounts _vehicleCoefficients;
};

} // namespace ParkingEngine

#endif /* PaymentManager_hpp */

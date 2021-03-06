#ifndef IPaymentManager_hpp
#define IPaymentManager_hpp

#include <stdio.h>
#include <iostream>

namespace ParkingEngine
{
class Session;
class ParkingPlace;
enum class VehicleType : std::uint8_t;

class IBasePaymentManager
{
public:
    virtual ~IBasePaymentManager() = default;
    
    virtual bool getPayment(EntryKeyID keyID) const = 0;
    
    virtual size_t getTotalPrice(EntryKeyID keyID) const = 0;
};

class IPaymentObservable
{
public:
    virtual ~IPaymentObservable() = default;
    
    virtual void registerObserver(IPaymentObserver* observer) = 0;
};

class IPaymentManager : public IBasePaymentManager, public IPaymentObservable
{
};

} // namespace ParkingEngine

#endif /* IPaymentManager_hpp */

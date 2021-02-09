#ifndef IPaymentObserver_h
#define IPaymentObserver_h

#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{

class IPaymentObserver
{
public:
    virtual ~IPaymentObserver() = default;
    
    virtual void onSuccessPayment(EntryKeyID keyID) = 0;
};

} // namespace ParkingEngine

#endif /* IPaymentObserver_h */

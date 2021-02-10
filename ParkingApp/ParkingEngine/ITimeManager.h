#ifndef ITimeManager_h
#define ITimeManager_h

#include "EntryKeyGenerator.hpp"
#include "IPaymentObserver.h"

namespace ParkingEngine
{
using TimeType = size_t;

class IBaseTimeManager
{
public:
    virtual ~IBaseTimeManager() = default;
    
    virtual void startSession(EntryKeyID keyID) = 0;
    
    virtual void stopSession(EntryKeyID keyID) = 0;
    
    virtual TimeType getSessionDuraton(EntryKeyID keyID) const = 0;
};

class ITimeManager : public IBaseTimeManager, public IPaymentObserver
{
};

} // namespace ParkingEngine

#endif /* ITimeManager_h */

#ifndef ITimeManager_h
#define ITimeManager_h

#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{
using TimeType = size_t;

class ITimeManager
{
public:
    virtual ~ITimeManager() = default;
    
    virtual void startSession(EntryKeyID keyID) = 0;
    
    virtual void stopSession(EntryKeyID keyID) = 0;
    
    virtual TimeType getSessionDuraton(EntryKeyID keyID) const = 0;
};

} // namespace ParkingEngine

#endif /* ITimeManager_h */

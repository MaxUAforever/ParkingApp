#ifndef TimeManager_hpp
#define TimeManager_hpp

#include "ITimeManager.h"

#include <stdio.h>
#include <unordered_map>

namespace ParkingEngine
{
class TimeManager : public ITimeManager
{
public:
    void startSession(EntryKeyID keyID) override;
    void stopSession(EntryKeyID keyID) override;
    TimeType getSessionDuraton(EntryKeyID keyID) const override;
    
private:
    size_t getCurrentTime() const;
    
private:
    std::unordered_map<EntryKeyID, TimeType> _sessionStartTimes;
};

} // namespace ParkingEngine

#endif /* TimeManager_hpp */

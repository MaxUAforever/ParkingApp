#include "TimeManager.hpp"

#include <cstdlib>
#include <iostream>

namespace ParkingEngine
{

void TimeManager::startSession(EntryKeyID keyID)
{
    _sessionStartTimes.emplace(keyID, getCurrentTime());
}

void TimeManager::stopSession(EntryKeyID keyID)
{
    _sessionStartTimes.erase(keyID);
}

TimeType TimeManager::getSessionDuraton(EntryKeyID keyID) const
{
    const auto startTimeIt = _sessionStartTimes.find(keyID);
    if (startTimeIt == _sessionStartTimes.end())
    {
        return 0;
    }
    
    const auto& startTime = startTimeIt->second;
    
    return getCurrentTime() - startTime;
}

size_t TimeManager::getCurrentTime() const
{
    // TODO: remove this code from function
    static size_t currentTime = 0;
    
    return currentTime++;
}

} // namespace ParkingEngine

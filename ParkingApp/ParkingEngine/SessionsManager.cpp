#include "SessionsManager.hpp"

namespace ParkingEngine
{

boost::optional<const SessionInfo&> SessionsManager::getSession(EntryKeyID keyID) const
{
    auto sessionIt = _sessions.find(keyID);
    if (sessionIt == _sessions.end())
    {
        return boost::none;
    }
    
    return sessionIt->second;
}

void SessionsManager::addSession(EntryKeyID keyID, SessionInfo&& session)
{
    _sessions.emplace(keyID, std::move(session));
}

bool SessionsManager::removeSession(EntryKeyID keyID)
{
    auto sessionIt = _sessions.find(keyID);
                            
    if (sessionIt == _sessions.end())
    {
        return false;
    }
    
    successReleaseNotify(sessionIt->second);
    
    _sessions.erase(sessionIt);
    
    return true;
}

void SessionsManager::registerObserver(ISessionObserver* observer)
{
    _observers.push_back(observer);
}

void SessionsManager::successReleaseNotify(SessionInfo session)
{
    for (auto observer : _observers)
    {
        observer->onSuccessRelease(session);
    }
}

} // namespace ParkingEngine

#ifndef ISessionsManager_h
#define ISessionsManager_h

#include <boost/optional.hpp>
#include <stdio.h>

#include "ISessionObserver.h"

#include "EntryKeyGenerator.hpp"
#include "SessionInfo.hpp"

namespace ParkingEngine
{
class ISessionsManager
{
public:
    virtual ~ISessionsManager() = default;
    
    virtual boost::optional<const SessionInfo&> getSession(EntryKeyID keyID) const = 0;
    
    virtual void addSession(EntryKeyID keyID, SessionInfo&& session) = 0;
    virtual bool removeSession(EntryKeyID keyID) = 0;
    
    virtual void registerObserver(ISessionObserver* observer) = 0;
};

} // namespace ParkingEngine

#endif /* ISessionsManager_h */

#ifndef SessionsManager_hpp
#define SessionsManager_hpp

#include "ISessionsManager.h"
#include "ISessionObserver.h"

#include <unordered_map>
#include <vector>

namespace ParkingEngine
{
using Sessions = std::unordered_map<EntryKeyID, SessionInfo>;

class SessionsManager : public ISessionsManager
{
public:
    boost::optional<const SessionInfo&> getSession(EntryKeyID keyID) const override;
    
    void addSession(EntryKeyID keyID, SessionInfo&& session) override;
    bool removeSession(EntryKeyID keyID) override;
    
    void registerObserver(ISessionObserver* observer) override;

private:
    void successReleaseNotify(SessionInfo session);
    
private:
    Sessions _sessions;

    std::vector<ISessionObserver*> _observers;
};

} // namespace ParkingEngine

#endif /* SessionsManager_hpp */

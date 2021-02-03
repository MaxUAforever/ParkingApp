#ifndef ClientsManager_hpp
#define ClientsManager_hpp

#include "IClientsManager.hpp"
#include "ISessionObserver.h"
#include "Client.hpp"
#include "SessionInfo.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <unordered_map>

namespace ParkingEngine
{

class ClientsManager : public IClientsManager
{
public:
    boost::optional<const Client&> getClient(EntryKeyID clientID) const override;
    void addClient(std::string name) override;
    
    bool addDiscount(EntryKeyID clientID, size_t durationTime) override;
    
    void onSuccessRelease(SessionInfo session) override;
    
private:
    std::unordered_map<EntryKeyID, Client> _clients;
};

} // namespace ParkingEngine

#endif /* ClientsManager_hpp */

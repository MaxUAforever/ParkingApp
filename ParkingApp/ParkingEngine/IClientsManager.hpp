#ifndef IClientsManager_hpp
#define IClientsManager_hpp

#include "Client.hpp"
#include "ISessionObserver.h"

#include <boost/optional.hpp>
#include <stdio.h>

namespace ParkingEngine
{

class IClientsManager : public ISessionObserver
{
public:
    virtual ~IClientsManager() = default;
    
    virtual boost::optional<const Client&> getClient(EntryKeyID clientID) const = 0;
    virtual void addClient(std::string name) = 0;
    
    virtual bool addDiscount(EntryKeyID clientID, size_t durationTime) = 0;
    
    virtual void onSuccessRelease(SessionInfo session) override = 0;
};

} // namespace ParkingEngine

#endif /* IClientsManager_hpp */

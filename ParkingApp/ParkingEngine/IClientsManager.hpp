#ifndef IClientsManager_hpp
#define IClientsManager_hpp

#include "Client.hpp"
#include "IPaymentObserver.h"

#include <boost/optional.hpp>
#include <stdio.h>

namespace ParkingEngine
{

class IBaseClientsManager
{
public:
    virtual ~IBaseClientsManager() = default;
    
    virtual boost::optional<const Client&> getClient(EntryKeyID clientID) const = 0;
    
    virtual void addClient(std::string name) = 0;
    
    virtual bool addDiscount(EntryKeyID clientID, size_t durationTime) = 0;
};

class IClientsManager : public IBaseClientsManager, public IPaymentObserver
{
};

} // namespace ParkingEngine

#endif /* IClientsManager_hpp */

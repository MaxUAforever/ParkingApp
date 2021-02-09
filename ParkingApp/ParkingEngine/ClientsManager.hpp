#ifndef ClientsManager_hpp
#define ClientsManager_hpp

#include "EntryKeyGenerator.hpp"
#include "TimeManager.hpp"
#include "IClientsManager.hpp"
#include "IPaymentObserver.h"
#include "Client.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <unordered_map>

namespace ParkingEngine
{

class ClientsManager : public IClientsManager
{
public:
    explicit ClientsManager(const TimeManager& timeManager);
    
    boost::optional<const Client&> getClient(EntryKeyID clientID) const override;
    void addClient(std::string name) override;
    
    bool addDiscount(EntryKeyID clientID, size_t durationTime) override;
    
    void onSuccessPayment(EntryKeyID clientID) override;
    
private:
    const TimeManager& _timeManager;
    std::unordered_map<EntryKeyID, Client> _clients;
};

} // namespace ParkingEngine

#endif /* ClientsManager_hpp */

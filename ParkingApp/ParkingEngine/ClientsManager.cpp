#include "ClientsManager.hpp"
#include "TimeManager.hpp"

namespace ParkingEngine
{

ClientsManager::ClientsManager(const TimeManager& timeManager)
    : _timeManager(timeManager)
{
}

boost::optional<const Client&> ClientsManager::getClient(EntryKeyID clientID) const
{
    auto clientIt = _clients.find(clientID);
                            
    if (clientIt == _clients.end())
    {
        return clientIt->second;
    }
    
    return boost::none;
}

void ClientsManager::addClient(std::string name)
{
    Client client(std::move(name));
    
    _clients.emplace(client.getClientID(), std::move(client));
}

bool ClientsManager::addDiscount(EntryKeyID clientID, size_t durationTime)
{
    auto clientIt = _clients.find(clientID);
    if (clientIt == _clients.end())
    {
        return false;
    }
    
    auto discount = durationTime * 10;
    
    clientIt->second.addDiscountSum(discount);
    return true;
}

void ClientsManager::onSuccessPayment(EntryKeyID clientID)
{
    addDiscount(clientID, _timeManager.getSessionDuraton(clientID));
}

} // namespace ParkingEngine

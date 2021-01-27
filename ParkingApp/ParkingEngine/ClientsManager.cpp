#include "ClientsManager.hpp"

namespace ParkingEngine
{

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
        auto discount = durationTime * 10;
        
        clientIt->second.addDiscountSum(discount);
        return true;
    }
    
    return false;
}

} // namespace ParkingEngine

#ifndef ClientsManager_hpp
#define ClientsManager_hpp

#include "Client.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <unordered_map>

namespace ParkingEngine
{

class ClientsManager
{
public:
    boost::optional<const Client&> getClient(EntryKeyID clientID) const;
    void addClient(std::string name);
    
    bool addDiscount(EntryKeyID clientID, size_t durationTime);
    
private:
    std::unordered_map<EntryKeyID, Client> _clients;
};

} // namespace ParkingEngine

#endif /* ClientsManager_hpp */

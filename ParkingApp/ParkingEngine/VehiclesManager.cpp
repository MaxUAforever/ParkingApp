#include "VehiclesManager.hpp"

#include "SessionInfo.hpp"

namespace ParkingEngine
{

boost::optional<const Vehicle&> VehiclesManager::getVehicle(EntryKeyID keyID) const
{
    auto vehicleIt = _vehicles.find(keyID);
                            
    if (vehicleIt == _vehicles.end())
    {
        return vehicleIt->second;
    }
    
    return boost::none;
}

void VehiclesManager::addVehicle(EntryKeyID keyID, const Vehicle& vehicle)
{
    _vehicles.emplace(keyID, vehicle);
}

bool VehiclesManager::removeVehicle(EntryKeyID keyID)
{
    auto vehicleIt = _vehicles.find(keyID);
    if (vehicleIt == _vehicles.end())
    {
        return false;
    }
    
    _vehicles.erase(vehicleIt);
    return true;
}


void VehiclesManager::onSuccessRelease(SessionInfo session)
{
    removeVehicle(session.getKeyID());
}

} // namespace ParkingEngine


#include "VehiclesManager.hpp"

#include "VehiclesRegisterService.hpp"

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

boost::optional<bool> VehiclesManager::checkIsVehicleForDisabled(EntryKeyID keyID) const
{
    auto vehicleIt = _vehicles.find(keyID);
    if (vehicleIt == _vehicles.end())
    {
        return false;
    }
    
    const auto& vehicle = vehicleIt->second;
    if (!vehicle.getRegNumber())
    {
        return false;
    }
    
    return VehiclesRegisterService::checkIsVehicleForDisabled(*vehicle.getRegNumber());
}

void VehiclesManager::onSuccessPayment(EntryKeyID keyID)
{
    removeVehicle(keyID);
}

} // namespace ParkingEngine


#ifndef VehiclesManager_hpp
#define VehiclesManager_hpp

#include <stdio.h>
#include <unordered_map>
#include <boost/optional.hpp>

#include "Vehicle.hpp"
#include "EntryKeyGenerator.hpp"
#include "IVehicleManager.h"

namespace ParkingEngine
{

class VehiclesManager : public IVehiclesManager
{
public:
    boost::optional<const Vehicle&> getVehicle(EntryKeyID keyID) const override;
    void addVehicle(EntryKeyID keyID, const Vehicle& vehicle) override;
    bool removeVehicle(EntryKeyID keyID) override;
    
    boost::optional<bool> checkIsVehicleForDisabled(EntryKeyID keyID) const override;
    
    void onSuccessPayment(EntryKeyID keyID) override;
    
private:
    std::unordered_map<EntryKeyID, Vehicle> _vehicles;
};

} // namespace ParkingEngine

#endif /* VehiclesManager_hpp */

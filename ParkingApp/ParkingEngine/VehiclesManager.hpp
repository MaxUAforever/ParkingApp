#ifndef VehiclesManager_hpp
#define VehiclesManager_hpp

#include <stdio.h>
#include <unordered_map>
#include <boost/optional.hpp>

#include "Vehicle.hpp"
#include "EntryKeyGenerator.hpp"
#include "ISessionObserver.h"

namespace ParkingEngine
{

class VehiclesManager : public ISessionObserver
{
public:
    boost::optional<const Vehicle&> getVehicle(EntryKeyID keyID) const;
    void addVehicle(EntryKeyID keyID, const Vehicle& vehicle);
    bool removeVehicle(EntryKeyID keyID);
    
    void onSuccessRelease(SessionInfo session) override;
    
private:
    std::unordered_map<EntryKeyID, Vehicle> _vehicles;
};

} // namespace ParkingEngine

#endif /* VehiclesManager_hpp */

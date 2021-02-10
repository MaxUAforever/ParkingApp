#ifndef IVehicleManager_h
#define IVehicleManager_h

#include "IPaymentObserver.h"

namespace ParkingEngine
{

class IBaseVehiclesManager
{
public:
    virtual ~IBaseVehiclesManager() = default;
    
    virtual boost::optional<const Vehicle&> getVehicle(EntryKeyID keyID) const = 0;
    
    virtual void addVehicle(EntryKeyID keyID, const Vehicle& vehicle) = 0;
    
    virtual bool removeVehicle(EntryKeyID keyID) = 0;
};

class IDisableVehiclesManager
{
public:
    virtual ~IDisableVehiclesManager() = default;
    
    virtual boost::optional<bool> checkIsVehicleForDisabled(EntryKeyID keyID) const = 0;
};

class IVehiclesManager : public IBaseVehiclesManager, public IDisableVehiclesManager, public IPaymentObserver
{
};

} // namespace ParkingEngine

#endif /* IVehicleManager_h */

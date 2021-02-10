#ifndef Parking_hpp
#define Parking_hpp

#include <stdio.h>
#include <map>
#include <unordered_map>
#include <vector>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include "Barrier.hpp"
#include "Vehicle.hpp"
#include "IBarrierObserver.hpp"
#include "IBarriersManager.hpp"
#include "IClientsManager.hpp"
#include "IPaymentManager.hpp"
#include "IStaffManager.hpp"
#include "ITimeManager.h"
#include "ParkingPlace.hpp"
#include "ParkingPlacesManager.hpp"
#include "Ticket.hpp"
#include "VehiclesManager.hpp"

namespace ParkingEngine
{
class PaymentManager;

enum class AccessErrorCode : std::uint8_t
{
    FullParking,
    NotEmptyPlace,
    DuplicateCarNumber,
    WrongPlaceID,
    WrongVehicleType,
    NotDisabledVehicle,
    NotAvailableVelRegService,
    NotSuccessfulPayment,
    BarrierIsBroken
};

using AccessResult = boost::variant<Ticket, AccessErrorCode>;

using Vehicles = std::unordered_map<EntryKeyID, Vehicle>;

class Parking : public IBarrierObserver
{
public:
    Parking(std::unique_ptr<ITimeManager> timeManager,
            std::unique_ptr<IPaymentManager> paymentManager,
            std::unique_ptr<IParkingPlacesManager> placesManager,
            std::unique_ptr<IClientsManager> clientsManager,
            std::unique_ptr<IStaffManager> staffManager,
            std::unique_ptr<IBarriersManager> barriersManager,
            std::unique_ptr<IVehiclesManager> vehiclesManager);

    AccessResult acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, boost::optional<EntryKeyID> clientID = boost::none);
    AccessResult acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, size_t placeID, boost::optional<EntryKeyID> clientID = boost::none);
    void releaseVehicle(EntryKeyID keyID, size_t barrierNumber);
    
    bool acceptStaff(EntryKeyID keyID, size_t barrierNumber);
    
    void onAlert(size_t barrierIndex) override;
    
    std::vector<PlaceID> getFreePlacesList() const;
    
private:
    void handleBarrierAlert(size_t barrierNumber, AccessErrorCode error);
    
    AccessResult reservePlace(EntryKeyID keyID, const Vehicle& vehicle, PlaceID placeID);
    
private:
    std::unique_ptr<ITimeManager> _timeManager;
    std::unique_ptr<IPaymentManager> _paymentManager;
    std::unique_ptr<IParkingPlacesManager> _placesManager;
    std::unique_ptr<IClientsManager> _clientsManager;
    std::unique_ptr<IStaffManager> _staffManager;
    std::unique_ptr<IBarriersManager> _barriersManager;
    std::unique_ptr<IVehiclesManager> _vehiclesManager;
};

} //namespace ParkingEngine

#endif /* Parking_hpp */

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
#include "ISessionsManager.h"
#include "IStaffManager.hpp"
#include "ParkingPlace.hpp"
#include "ParkingPlacesManager.hpp"
#include "PaymentService.hpp"
#include "SessionInfo.hpp"
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
    WrongPlaceNumber,
    WrongVehicleType,
    NotDisabledVehicle,
    NotAvailableVelRegService
};

using AccessResult = boost::variant<Ticket, AccessErrorCode>;

using Vehicles = std::unordered_map<EntryKeyID, Vehicle>;

class Parking : public IBarrierObserver
{
public:
    Parking(std::unique_ptr<IPaymentManager> paymentManager,
            std::unique_ptr<IParkingPlacesManager> placesManager,
            std::unique_ptr<IClientsManager> clientsManager,
            std::unique_ptr<IStaffManager> staffManager,
            std::unique_ptr<IBarriersManager> barriersManager,
            std::unique_ptr<ISessionsManager> sessionsManager);

    AccessResult acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, boost::optional<EntryKeyID> clientID = boost::none);
    AccessResult acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, size_t placeNumber, boost::optional<EntryKeyID> clientID = boost::none);
    void releaseVehicle(EntryKeyID keyID, const Vehicle& vehicle, size_t barrierNumber);
    
    bool acceptStaff(EntryKeyID keyID, size_t barrierNumber);
    
    void onAlert(size_t barrierIndex) override;
    
    std::vector<PlaceNumber> getFreePlacesList() const;
    
private:
    void handleBarrierAlert(size_t barrierNumber);
    
    AccessResult reservePlace(EntryKeyID keyID, const Vehicle& vehicle, PlaceNumber placeNumber);
    
private:
    std::unique_ptr<IPaymentManager> _paymentManager;
    std::unique_ptr<IParkingPlacesManager> _placesManager;
    std::unique_ptr<IClientsManager> _clientsManager;
    std::unique_ptr<IStaffManager> _staffManager;
    std::unique_ptr<IBarriersManager> _barriersManager;
    std::unique_ptr<ISessionsManager> _sessionsManager;
    std::unique_ptr<VehiclesManager> _vehiclesManager;
    PaymentService _paymentService;
};

} //namespace ParkingEngine

#endif /* Parking_hpp */

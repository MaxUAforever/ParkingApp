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
#include "PaymentManager.hpp"
#include "ParkingPlace.hpp"
#include "ParkingPlacesManager.hpp"
#include "SessionInfo.hpp"
#include "StaffManager.hpp"
#include "ClientsManager.hpp"
#include "Ticket.hpp"

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
using Sessions = std::unordered_map<EntryKeyID, SessionInfo>;
using Barriers = std::vector<Barrier>;

class Parking : public IBarrierObserver
{
public:
    Parking(size_t placesCount, size_t barriersCount);

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
    PaymentManager _paymentManager;
    ParkingPlacesManager _placesManager;
    ClientsManager _clientsManager;
    StaffManager _staffManager;
    Barriers _barriers;
    Sessions _sessions;
    Vehicles _vehicles;
};

} //namespace ParkingEngine

#endif /* Parking_hpp */

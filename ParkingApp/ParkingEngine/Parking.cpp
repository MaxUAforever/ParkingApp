#include "Parking.hpp"

#include "TimeManager.hpp"
#include "VelichesRegisterService.hpp"
#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{
Parking::Parking(std::unique_ptr<IPaymentManager> paymentManager,
                 std::unique_ptr<IParkingPlacesManager> placesManager,
                 std::unique_ptr<IClientsManager> clientsManager,
                 std::unique_ptr<IStaffManager> staffManager,
                 std::unique_ptr<IBarriersManager> barriersManager,
                 std::unique_ptr<ISessionsManager> sessionsManager)
    : _paymentManager(std::move(paymentManager))
    , _placesManager(std::move(placesManager))
    , _clientsManager(std::move(clientsManager))
    , _staffManager(std::move(staffManager))
    , _barriersManager(std::move(barriersManager))
    , _sessionsManager(std::move(sessionsManager))
{
    _vehiclesManager = std::make_unique<VehiclesManager>();
    _barriersManager->registerBarriersObserver(this);
    
    _paymentManager->setVelicheCoefficient(VehicleType::Motorbyke, 0.5);
    _paymentManager->setVelicheCoefficient(VehicleType::Truck, 2);
    
    _sessionsManager->registerObserver(&*_placesManager);
    _sessionsManager->registerObserver(&*_clientsManager);
    _sessionsManager->registerObserver(&*_vehiclesManager);
}

AccessResult Parking::reservePlace(EntryKeyID keyID, const Vehicle& vehicle, PlaceNumber placeNumber)
{
    if (_sessionsManager->getSession(keyID))
    {
        return AccessErrorCode::DuplicateCarNumber;
    }
    
    if (!_placesManager->reservePlace(placeNumber))
    {
        return AccessErrorCode::NotEmptyPlace;
    }
    
    auto session = SessionInfo(keyID, vehicle.getRegNumber(), placeNumber, TimeManager::getCurrentTime());
    
    _sessionsManager->addSession(keyID, std::move(session));
    _vehiclesManager->addVehicle(keyID, vehicle);
    
    return Ticket(keyID, placeNumber);
}

AccessResult Parking::acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, boost::optional<EntryKeyID> clientID)
{
    const auto keyID = clientID ? *clientID : EntryKeyGenerator::generateKey();
    
    const auto& freeSuitablePlaces = _placesManager->getFreePlacesList(vehicle.getType());
    if (freeSuitablePlaces.empty())
    {
        return AccessErrorCode::FullParking;
    }
    
    return reservePlace(keyID, vehicle, freeSuitablePlaces.at(0));
}

AccessResult Parking::acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, size_t placeNumber, boost::optional<EntryKeyID> clientID)
{
    const auto keyID = clientID ? *clientID : EntryKeyGenerator::generateKey();
    
    if (_placesManager->isParkingFull())
    {
        return AccessErrorCode::FullParking;
    }

    const auto& place = _placesManager->getPlace(placeNumber);
    if (!place)
    {
        return AccessErrorCode::WrongPlaceNumber;
    }
    
    if (place->isForDisabledPerson())
    {
        auto isVehicleForDisabled = VelichesRegisterService::checkIsVehicleForDisabled(vehicle.getRegNumber());
        
        if (!isVehicleForDisabled)
        {
            handleBarrierAlert(barrierNumber);
            
            return AccessErrorCode::NotAvailableVelRegService;
        }
        if (!*isVehicleForDisabled)
        {
            return AccessErrorCode::NotDisabledVehicle;
        }
    }
    
    if (place->getVehicleType() != vehicle.getType())
    {
        return AccessErrorCode::WrongVehicleType;
    }
    
    return reservePlace(keyID, vehicle, placeNumber);
}

bool Parking::acceptStaff(EntryKeyID keyID, size_t barrierNumber)
{
    if (_staffManager->getStaff(keyID))
    {
        _barriersManager->openBarrier(barrierNumber);
        return true;
    }
    
    return false;
}

void Parking::releaseVehicle(EntryKeyID keyID, const Vehicle& vehicle, size_t barrierNumber)
{
    auto session = _sessionsManager->getSession(keyID);
    if (!session)
    {
        handleBarrierAlert(barrierNumber);
        return;
    }
    
    const auto& place = _placesManager->getPlace(session->getPlaceNumber());
    if (!place)
    {
        handleBarrierAlert(barrierNumber);
        return;
    }
    
    const auto price = _paymentManager->getTotalPrice(*session, *place);
    if (!_paymentService.getPayment(price))
    {
        handleBarrierAlert(barrierNumber);
        return;
    }
    
    _sessionsManager->removeSession(keyID);
   
    if (!_barriersManager->openBarrier(barrierNumber))
    {
        handleBarrierAlert(barrierNumber);
        return;
    }
}

void Parking::onAlert(size_t barrierNumber)
{
    handleBarrierAlert(barrierNumber);
}

void Parking::handleBarrierAlert(size_t barrierNumber)
{
    std::cout << "Operator is needed on " << barrierNumber << " barrier.\n";
    return;
}

std::vector<PlaceNumber> Parking::getFreePlacesList() const
{
    return _placesManager->getFreePlacesList();
}

} // namespace ParkingEngine

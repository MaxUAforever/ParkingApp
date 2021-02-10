#include "Parking.hpp"

#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{

Parking::Parking(std::unique_ptr<ITimeManager> timeManager,
                 std::unique_ptr<IPaymentManager> paymentManager,
                 std::unique_ptr<IParkingPlacesManager> placesManager,
                 std::unique_ptr<IClientsManager> clientsManager,
                 std::unique_ptr<IStaffManager> staffManager,
                 std::unique_ptr<IBarriersManager> barriersManager,
                 std::unique_ptr<IVehiclesManager> vehiclesManager)
    : _timeManager(std::move(timeManager))
    , _paymentManager(std::move(paymentManager))
    , _placesManager(std::move(placesManager))
    , _clientsManager(std::move(clientsManager))
    , _staffManager(std::move(staffManager))
    , _barriersManager(std::move(barriersManager))
    , _vehiclesManager(std::move(vehiclesManager))
{
    _barriersManager->registerBarriersObserver(this);
    
    _paymentManager->registerObserver(&*_placesManager);
    _paymentManager->registerObserver(&*_clientsManager);
    _paymentManager->registerObserver(&*_vehiclesManager);
    _paymentManager->registerObserver(&*_timeManager);
}

AccessResult Parking::reservePlace(EntryKeyID keyID, const Vehicle& vehicle, PlaceID placeID)
{
    if (!_placesManager->reservePlace(keyID, placeID))
    {
        return AccessErrorCode::NotEmptyPlace;
    }
    
    _timeManager->startSession(keyID);
    _vehiclesManager->addVehicle(keyID, vehicle);
    
    return Ticket(keyID, placeID);
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

AccessResult Parking::acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, size_t placeID, boost::optional<EntryKeyID> clientID)
{
    const auto keyID = clientID ? *clientID : EntryKeyGenerator::generateKey();
    
    if (_placesManager->isParkingFull())
    {
        return AccessErrorCode::FullParking;
    }

    const auto& place = _placesManager->getPlace(placeID);
    if (!place)
    {
        return AccessErrorCode::WrongPlaceID;
    }
    
    if (place->isForDisabledPerson())
    {
        auto isVehicleForDisabled = _vehiclesManager->checkIsVehicleForDisabled(keyID);
        
        if (!isVehicleForDisabled)
        {
            handleBarrierAlert(barrierNumber, AccessErrorCode::NotAvailableVelRegService);
            
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
    
    return reservePlace(keyID, vehicle, placeID);
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

void Parking::releaseVehicle(EntryKeyID keyID, size_t barrierNumber) 
{
    const auto isSuccessPayment = _paymentManager->getPayment(keyID);
    
    if (!isSuccessPayment)
    {
        handleBarrierAlert(barrierNumber, AccessErrorCode::NotSuccessfulPayment);
        return;
    }
   
    if (!_barriersManager->openBarrier(barrierNumber))
    {
        handleBarrierAlert(barrierNumber, AccessErrorCode::BarrierIsBroken);
        return;
    }
}

void Parking::onAlert(size_t barrierNumber)
{
    handleBarrierAlert(barrierNumber, AccessErrorCode::BarrierIsBroken);
}

void Parking::handleBarrierAlert(size_t barrierNumber, AccessErrorCode error)
{
    std::cout << "Operator is needed on " << barrierNumber << " barrier.\n";
    
    switch(error)
    {
        case AccessErrorCode::FullParking: std::cout << "FullParking" << std::endl; break;
        case AccessErrorCode::NotEmptyPlace: std::cout << "NotEmptyPlace" << std::endl; break;
        case AccessErrorCode::DuplicateCarNumber: std::cout << "DuplicateCarNumber" << std::endl; break;
        case AccessErrorCode::WrongPlaceID: std::cout << "WrongPlaceID" << std::endl; break;
        case AccessErrorCode::WrongVehicleType: std::cout << "WrongVehicleType" << std::endl; break;
        case AccessErrorCode::NotDisabledVehicle: std::cout << "NotDisabledVehicle" << std::endl; break;
        case AccessErrorCode::NotAvailableVelRegService: std::cout << "NotAvailableVelRegService" << std::endl; break;
        case AccessErrorCode::NotSuccessfulPayment: std::cout << "NotSuccessfulPayment" << std::endl; break;
        case AccessErrorCode::BarrierIsBroken: std::cout << "BarrierIsBroken" << std::endl; break;
    }
    
    return;
}

std::vector<PlaceID> Parking::getFreePlacesList() const
{
    return _placesManager->getFreePlacesList();
}

} // namespace ParkingEngine

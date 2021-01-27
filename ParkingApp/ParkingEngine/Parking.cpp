#include "Parking.hpp"

#include "PaymentService.hpp"
#include "TimeManager.hpp"
#include "VelichesRegisterService.hpp"
#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{
Parking::Parking(size_t placesCount, size_t barriersCount)
    : _placesManager(placesCount)
    , _paymentManager(100, 0.8, 10)
{
    _barriers.reserve(barriersCount);
    for (auto i = 1; i <= barriersCount; ++i)
    {
        _barriers.emplace_back(i);
        _barriers.back().registerObserver(this);
    }
    
    _paymentManager.setVelicheCoefficient(VehicleType::Motorbyke, 0.5);
    _paymentManager.setVelicheCoefficient(VehicleType::Truck, 2);
}

AccessResult Parking::reservePlace(EntryKeyID keyID, const Vehicle& vehicle, PlaceNumber placeNumber)
{
    auto sessionIt = _sessions.find(keyID);
    if (sessionIt != _sessions.end())
    {
        return AccessErrorCode::DuplicateCarNumber;
    }
    
    if (!_placesManager.reservePlace(placeNumber))
    {
        return AccessErrorCode::NotEmptyPlace;
    }
    
    auto session = SessionInfo(vehicle.getRegNumber(), placeNumber, TimeManager::getCurrentTime());
    
    _sessions.emplace(keyID, std::move(session));
    _vehicles.emplace(keyID, vehicle);
    
    return Ticket(keyID, placeNumber);
}

AccessResult Parking::acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, boost::optional<EntryKeyID> clientID)
{
    const auto keyID = clientID ? *clientID : EntryKeyGenerator::generateKey();
    
    const auto& freeSuitablePlaces = _placesManager.getFreePlacesList(vehicle.getType());
    if (freeSuitablePlaces.empty())
    {
        return AccessErrorCode::FullParking;
    }
    
    return reservePlace(keyID, vehicle, freeSuitablePlaces.at(0));
}

AccessResult Parking::acceptVehicle(const Vehicle& vehicle, size_t barrierNumber, size_t placeNumber, boost::optional<EntryKeyID> clientID)
{
    const auto keyID = clientID ? *clientID : EntryKeyGenerator::generateKey();
    
    if (_placesManager.isParkingFull())
    {
        return AccessErrorCode::FullParking;
    }

    const auto& place = _placesManager.getPlace(placeNumber);
    if (!place)
    {
        return AccessErrorCode::WrongPlaceNumber;
    }
    
    if (place->isForDisabledPerson())
    {
        auto isVehicleForDisabled = Externals::VelichesRegisterService::checkIsVehicleForDisabled(vehicle.getRegNumber());
        
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
    if (_staffManager.getStaff(keyID))
    {
        _barriers[barrierNumber].open();
        return true;
    }
    
    return false;
}

void Parking::releaseVehicle(EntryKeyID keyID, const Vehicle& vehicle, size_t barrierNumber)
{
    auto sessionIt = _sessions.find(keyID);
    auto vehicleIt = _vehicles.find(keyID);
                            
    if (sessionIt == _sessions.end() || vehicleIt == _vehicles.end())
    {
        onAlert(barrierNumber);
        return;
    }
    
    const auto& session = sessionIt->second;
    if (const auto& place = _placesManager.getPlace(session.getPlaceNumber()))
    {
        const auto price = _paymentManager.getTotalPrice(session, *place);
        
        if (PaymentService::getPayment(price))
        {
            _placesManager.releasePlace(session.getPlaceNumber());
            _sessions.erase(sessionIt);
            _vehicles.erase(vehicleIt);
            
            _clientsManager.addDiscount(keyID, TimeManager::getCurrentTime() - session.getStartTime());
            
            if (_barriers.at(barrierNumber).open())
            {
                return;
            }
        }
    }
    
    handleBarrierAlert(barrierNumber);
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
    return _placesManager.getFreePlacesList();
}

} // namespace ParkingEngine

#include "Parking.hpp"

#include "PaymentService.hpp"
#include "TimeManager.hpp"

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

AccessResult Parking::reservePlace(const Car& car, PlaceNumber placeNumber)
{
    auto ticketIt = _tickets.find(car.getRegNumber());
    if (ticketIt != _tickets.end())
    {
        return AccessErrorCode::DuplicateCarNumber;
    }
    
    if (!_placesManager.reservePlace(placeNumber))
    {
        return AccessErrorCode::NotEmptyPlace;
    }
    
    const auto ticket = Ticket(car.getRegNumber(), placeNumber, TimeManager::getCurrentTime());
    _tickets.emplace(car.getRegNumber(), ticket);
    _cars.emplace(car.getRegNumber(), car);
    
    return _tickets.at(car.getRegNumber());
}

AccessResult Parking::acceptCar(const Car& car, size_t barrierNumber)
{
    if (_placesManager.isParkingFull())
    {
        return AccessErrorCode::FullParking;
    }
    
    return reservePlace(car, _placesManager.getFreePlacesList().at(0));
}

AccessResult Parking::acceptCar(const Car& car, size_t barrierNumber, size_t placeNumber)
{
    if (_placesManager.isParkingFull())
    {
        return AccessErrorCode::FullParking;
    }

    return reservePlace(car, placeNumber);
}

void Parking::releaseCar(const Car& car, size_t barrierNumber)
{
    auto ticketIt = _tickets.find(car.getRegNumber());
    auto carIt = _cars.find(car.getRegNumber());
                            
    if (ticketIt == _tickets.end() || carIt == _cars.end())
    {
        onAlert(barrierNumber);
        return;
    }
    
    const auto& ticket = ticketIt->second;
    if (const auto& place = _placesManager.getPlace(ticket.getPlaceNumber()))
    {
        const auto price = _paymentManager.getTotalPrice(ticket, *place);
        
        if (PaymentService::getPayment(price))
        {
            _placesManager.releasePlace(ticket.getPlaceNumber());
            _tickets.erase(ticketIt);
            _cars.erase(carIt);
            
            _barriers.at(barrierNumber).open();
            return;
        }
    }
    
    handleBarrierAlert(barrierNumber);
}

void Parking::onAlert(size_t barrierNumber)
{
    handleBarrierAlert(barrierNumber);
}

void handleBarrierAlert(size_t barrierNumber)
{
    std::cout << "Operator is needed on " << barrierNumber << " barrier.\n";
    return;
}

std::vector<PlaceNumber> Parking::getFreePlacesList() const
{
    return _placesManager.getFreePlacesList();
}

} // namespace ParkingEngine

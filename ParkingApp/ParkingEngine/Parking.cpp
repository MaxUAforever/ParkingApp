#include "Parking.hpp"

#include "PaymentService.hpp"
#include "TimeManager.hpp"

namespace ParkingEngine
{
Parking::Parking(size_t placesCount, size_t barriersCount)
    : _placesManager(placesCount)
{
    _barriers.reserve(barriersCount);
    for (auto i = 1; i <= barriersCount; ++i)
    {
        _barriers.emplace_back(i);
        _barriers.back().registerObserver(this);
    }
}

AccessResult Parking::reservePlace(const Car& car, PlaceIndex placeIndex)
{
    auto ticketIt = _tickets.find(car.getRegNumber());
    if (ticketIt != _tickets.end())
    {
        return AccessErrorCode::DuplicateCarNumber;
    }
    
    if (!_placesManager.reservePlace(placeIndex))
    {
        return AccessErrorCode::NotEmptyPlace;
    }
    
    const auto ticket = Ticket(car.getRegNumber(), placeIndex, TimeManager::getCurrentTime());
    _tickets.insert({car.getRegNumber(), ticket});
    _cars.insert({car.getRegNumber(), car});
    
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

AccessResult Parking::acceptCar(const Car& car, size_t barrierNumber, size_t placeIndex)
{
    if (_placesManager.isParkingFull())
    {
        return AccessErrorCode::FullParking;
    }

    return reservePlace(car, placeIndex);
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
    if (const auto& place = _placesManager.getPlace(ticket.getPlaceIndex()))
    {
        const auto durationTime = TimeManager::getCurrentTime() - ticket.getStartTime();
        const auto price = place->getPrice() * durationTime;
        
        if (PaymentService::getPayment(price))
        {
            _placesManager.releasePlace(ticket.getPlaceIndex());
            _tickets.erase(ticketIt);
            _cars.erase(carIt);
            
            _barriers.at(barrierNumber).open();
            return;
        }
    }
    
    onAlert(barrierNumber);
}

void Parking::onAlert(size_t barrierIndex)
{
    std::cout << "Operator is needed on " << barrierIndex << " barrier.\n";
    return;
}

std::vector<PlaceIndex> Parking::getFreePlacesList() const
{
    return _placesManager.getFreePlacesList();
}

} // namespace ParkingEngine

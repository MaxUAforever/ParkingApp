#include "Parking.hpp"

#include "PaymentService.hpp"
#include "TimeManager.hpp"

namespace ParkingEngine
{
Parking::Parking(size_t placesCount, size_t barriersCount)
{
    for (PlaceIndex i = 1; i <= placesCount; ++i)
    {
        _freePlaces.insert({i, ParkingPlace(i)});
    }
}

AccessResult Parking::reservePlace(const Car& car, ParkingPlaces::iterator placeIt)
{
    auto ticketIt = _tickets.find(car.getRegNumber());
    if (ticketIt != _tickets.end())
    {
        return AccessErrorCode::DuplicateCarNumber;
    }
    
    const auto ticket = Ticket(car, std::move(placeIt->second), 0);
    _tickets.insert({car.getRegNumber(), ticket});
    _freePlaces.erase(placeIt);
    
    return _tickets.at(car.getRegNumber());
}

AccessResult Parking::acceptCar(const Car& car, int barrierNumber)
{
    if (_freePlaces.empty())
    {
        return AccessErrorCode::FullParking;
    }
    
    auto placeIt = _freePlaces.begin();
    return reservePlace(car, placeIt);
}

AccessResult Parking::acceptCar(const Car& car, int barrierNumber, size_t placeIndex)
{
    if (_freePlaces.empty())
    {
        return AccessErrorCode::FullParking;
    }
    
    auto placeIt = _freePlaces.find(placeIndex);
    if (placeIt == _freePlaces.end())
    {
        return AccessErrorCode::NotEmptyPlace;
    }

    return reservePlace(car, placeIt);
}

void Parking::releaseCar(const Car& car, int barrierNumber)
{
    auto ticketIt = _tickets.find(car.getRegNumber());
    if (ticketIt != _tickets.end())
    {
        auto place = ticketIt->second.getPlace();
        const auto& ticket = ticketIt->second;
        
        const auto durationTime = TimeManager::getCurrentTime() - ticket.getStartTime();
        const auto price = place.getPrice() * durationTime;
        
        if (PaymentService::getPayment(price))
        {
            _freePlaces.insert({place.getNumber(), place});
            _tickets.erase(ticketIt);
        }
    }
    
    // TODO: call operator to barrier.
}

std::vector<PlaceIndex> Parking::getFreePlacesList() const
{
    std::vector<PlaceIndex> freePlacesIndexes;
    freePlacesIndexes.reserve(_freePlaces.size());
    
    for (auto place : _freePlaces)
    {
        freePlacesIndexes.push_back(place.first);
    }
    
    return freePlacesIndexes;
}

} // namespace ParkingEngine

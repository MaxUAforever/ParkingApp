#include "ParkingPlacesManager.hpp"

#include <vector>

namespace ParkingEngine
{

ParkingPlacesManager::ParkingPlacesManager(size_t placesCount)
{
    for (PlaceNumber i = 1; i <= placesCount; ++i)
    {
        _places.emplace(i, ParkingPlace(i));
        _freePlaces.emplace(i);
    }
}

boost::optional<const ParkingPlace&> ParkingPlacesManager::getPlace(PlaceNumber placeNumber) const
{
    auto placeIt = _places.find(placeNumber);
    if (placeIt != _places.end())
    {
        return placeIt->second;
    }
    
    return boost::none;
}

boost::optional<const ParkingPlace&> ParkingPlacesManager::getReservedPlace(EntryKeyID keyID) const
{
    auto placeIt = _reservedPlaces.find(keyID);
    if (placeIt != _reservedPlaces.end())
    {
        return _places.at(placeIt->second);
    }
    
    return boost::none;
}

bool ParkingPlacesManager::reserveFreePlace(EntryKeyID clientID)
{
    if (isParkingFull())
    {
        return false;
    }
    
    const auto& placeNumber = _freePlaces.begin();
    return reservePlace(clientID, *placeNumber);
}

bool ParkingPlacesManager::reservePlace(EntryKeyID clientID, PlaceNumber placeNumber)
{
    auto placeIt = _freePlaces.find(placeNumber);
    if (placeIt == _freePlaces.end())
    {
        return false;
    }
    
    _reservedPlaces.emplace(clientID, std::move(*placeIt));
    _freePlaces.erase(placeIt);
    
    return true;
}

// TODO: change to void?
bool ParkingPlacesManager::releasePlace(EntryKeyID clientID)
{
    auto reservedPlaceIt = _reservedPlaces.find(clientID);
    if (reservedPlaceIt == _reservedPlaces.end())
    {
        return false;
    }
    
    auto placeNumber = reservedPlaceIt->second;
    
    _freePlaces.emplace(std::move(placeNumber));
    _reservedPlaces.erase(reservedPlaceIt);
    
    return true;
}

bool ParkingPlacesManager::isParkingFull() const
{
    return _freePlaces.empty();
}

std::vector<PlaceNumber> ParkingPlacesManager::getFreePlacesList() const
{
    return getFreePlacesListByParam([](const ParkingPlace&)
                                {
                                    return true;
                                });
}

std::vector<PlaceNumber> ParkingPlacesManager::getFreePlacesList(VehicleType vehicleType) const
{
    return getFreePlacesListByParam([&](const ParkingPlace& place)
                                {
                                    return place.getVehicleType() == vehicleType;
                                });
}

std::vector<PlaceNumber> ParkingPlacesManager::getFreePlacesList(bool isForDisabledPerson) const
{
    return getFreePlacesListByParam([&](const ParkingPlace& place)
                                {
                                    return place.isForDisabledPerson() == isForDisabledPerson;
                                });
}

std::vector<PlaceNumber> ParkingPlacesManager::getFreePlacesListByParam(IsPlaceSuitableFunc isSuitableFunc) const
{
    std::vector<PlaceNumber> freePlacesIndexes;
    
    for (const auto& placeID : _freePlaces)
    {
        const auto& place = _places.at(placeID);
        
        if (isSuitableFunc(place))
        {
            freePlacesIndexes.emplace_back(place.getNumber());
        }
    }
    
    return freePlacesIndexes;
}

void ParkingPlacesManager::onSuccessPayment(EntryKeyID clientID)
{
    releasePlace(clientID);
}

} // namespace ParkingEngine

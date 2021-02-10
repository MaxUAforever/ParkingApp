#include "ParkingPlacesManager.hpp"

#include <vector>

namespace ParkingEngine
{

ParkingPlacesManager::ParkingPlacesManager(size_t placesCount)
{
    for (PlaceID i = 1; i <= placesCount; ++i)
    {
        _places.emplace(i, ParkingPlace(i));
        _freePlaces.emplace(i);
    }
}

boost::optional<const ParkingPlace&> ParkingPlacesManager::getPlace(PlaceID placeID) const
{
    auto placeIt = _places.find(placeID);
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
    
    const auto& placeID = _freePlaces.begin();
    return reservePlace(clientID, *placeID);
}

bool ParkingPlacesManager::reservePlace(EntryKeyID clientID, PlaceID placeID)
{
    auto placeIt = _freePlaces.find(placeID);
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
    
    auto placeID = reservedPlaceIt->second;
    
    _freePlaces.emplace(std::move(placeID));
    _reservedPlaces.erase(reservedPlaceIt);
    
    return true;
}

bool ParkingPlacesManager::isParkingFull() const
{
    return _freePlaces.empty();
}

std::vector<PlaceID> ParkingPlacesManager::getFreePlacesList() const
{
    return getFreePlacesListByParam([](const ParkingPlace&)
                                {
                                    return true;
                                });
}

std::vector<PlaceID> ParkingPlacesManager::getFreePlacesList(VehicleType vehicleType) const
{
    return getFreePlacesListByParam([&](const ParkingPlace& place)
                                {
                                    return place.getVehicleType() == vehicleType;
                                });
}

std::vector<PlaceID> ParkingPlacesManager::getFreePlacesList(bool isForDisabledPerson) const
{
    return getFreePlacesListByParam([&](const ParkingPlace& place)
                                {
                                    return place.isForDisabledPerson() == isForDisabledPerson;
                                });
}

std::vector<PlaceID> ParkingPlacesManager::getFreePlacesListByParam(IsPlaceSuitableFunc isSuitableFunc) const
{
    std::vector<PlaceID> freePlacesIndexes;
    
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

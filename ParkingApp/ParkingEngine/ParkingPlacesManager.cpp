#include "ParkingPlacesManager.hpp"

#include <vector>

namespace ParkingEngine
{

ParkingPlacesManager::ParkingPlacesManager(size_t placesCount)
{
    for (PlaceIndex i = 1; i <= placesCount; ++i)
    {
        _freePlaces.insert({i, ParkingPlace(i)});
    }
}

boost::optional<const ParkingPlace&> ParkingPlacesManager::getPlace(PlaceIndex placeIndex) const
{
    auto freePaceIt = _freePlaces.find(placeIndex);
    if (freePaceIt != _freePlaces.end())
    {
        return freePaceIt->second;
    }
    
    auto reservedPlaceIt = _reservedPlaces.find(placeIndex);
    if (reservedPlaceIt != _freePlaces.end())
    {
        return reservedPlaceIt->second;
    }
    
    return boost::none;
}

bool ParkingPlacesManager::reserveFreePlace()
{
    if (isParkingFull())
    {
        return false;
    }
    
    const auto& placeIndex = _freePlaces.begin()->first;
    return reservePlace(placeIndex);
}

bool ParkingPlacesManager::reservePlace(PlaceIndex placeIndex)
{
    auto placeIt = _freePlaces.find(placeIndex);
    if (placeIt == _freePlaces.end())
    {
        return false;
    }
    
    _reservedPlaces.insert({placeIndex, std::move(placeIt->second)});
    _freePlaces.erase(placeIt);
    
    return true;
}

bool ParkingPlacesManager::releasePlace(PlaceIndex placeIndex)
{
    auto reservedPlaceIt = _reservedPlaces.find(placeIndex);
    if (reservedPlaceIt != _freePlaces.end())
    {
        _freePlaces.insert({placeIndex, std::move(reservedPlaceIt->second)});
        _reservedPlaces.erase(reservedPlaceIt);
        
        return true;
    }
    
    return false;
}

bool ParkingPlacesManager::isParkingFull() const
{
    return _freePlaces.empty();
}

std::vector<PlaceIndex> ParkingPlacesManager::getFreePlacesList() const
{
    std::vector<PlaceIndex> freePlacesIndexes;
    
    for (const auto& placeInfo : _freePlaces)
    {
        const auto& place = placeInfo.second;
        
        freePlacesIndexes.push_back(place.getNumber());
    }
    
    return freePlacesIndexes;
}

} // namespace ParkingEngine

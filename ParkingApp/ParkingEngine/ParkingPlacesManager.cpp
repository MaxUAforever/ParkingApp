#include "ParkingPlacesManager.hpp"

#include <vector>

namespace ParkingEngine
{

ParkingPlacesManager::ParkingPlacesManager(size_t placesCount)
{
    for (PlaceNumber i = 1; i <= placesCount; ++i)
    {
        _freePlaces.insert({i, ParkingPlace(i)});
    }
}

boost::optional<const ParkingPlace&> ParkingPlacesManager::getPlace(PlaceNumber placeNumber) const
{
    auto freePaceIt = _freePlaces.find(placeNumber);
    if (freePaceIt != _freePlaces.end())
    {
        return freePaceIt->second;
    }
    
    auto reservedPlaceIt = _reservedPlaces.find(placeNumber);
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
    
    const auto& placeNumber = _freePlaces.begin()->first;
    return reservePlace(placeNumber);
}

bool ParkingPlacesManager::reservePlace(PlaceNumber placeNumber)
{
    auto placeIt = _freePlaces.find(placeNumber);
    if (placeIt == _freePlaces.end())
    {
        return false;
    }
    
    _reservedPlaces.insert({placeNumber, std::move(placeIt->second)});
    _freePlaces.erase(placeIt);
    
    return true;
}

bool ParkingPlacesManager::releasePlace(PlaceNumber placeNumber)
{
    auto reservedPlaceIt = _reservedPlaces.find(placeNumber);
    if (reservedPlaceIt != _freePlaces.end())
    {
        _freePlaces.insert({placeNumber, std::move(reservedPlaceIt->second)});
        _reservedPlaces.erase(reservedPlaceIt);
        
        return true;
    }
    
    return false;
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
    
    for (const auto& placeInfo : _freePlaces)
    {
        const auto& place = placeInfo.second;
        
        if (isSuitableFunc(place))
        {
            freePlacesIndexes.emplace_back(place.getNumber());
        }
    }
    
    return freePlacesIndexes;
}

void ParkingPlacesManager::onSuccessRelease(SessionInfo session)
{
    releasePlace(session.getPlaceNumber());
}

} // namespace ParkingEngine

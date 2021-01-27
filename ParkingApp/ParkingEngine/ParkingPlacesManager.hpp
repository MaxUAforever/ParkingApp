#ifndef ParkingPlacesManager_hpp
#define ParkingPlacesManager_hpp

#include "Vehicle.hpp"
#include "ParkingPlace.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <map>

namespace ParkingEngine
{
using ParkingPlaces = std::map<PlaceNumber, ParkingPlace>;
using IsPlaceSuitableFunc = std::function<bool(const ParkingPlace&)>;

class ParkingPlacesManager
{
public:
    ParkingPlacesManager(size_t placesCount);
    
    boost::optional<const ParkingPlace&> getPlace(PlaceNumber placeNumber) const;
    
    bool reserveFreePlace();
    bool reservePlace(PlaceNumber placeNumber);
    bool releasePlace(PlaceNumber placeNumber);
    
    bool isParkingFull() const;
    std::vector<PlaceNumber> getFreePlacesList() const;
    std::vector<PlaceNumber> getFreePlacesList(VehicleType vehicleType) const;
    std::vector<PlaceNumber> getFreePlacesList(bool isForDisabledPerson) const;
    
private:
    std::vector<PlaceNumber> getFreePlacesListByParam(IsPlaceSuitableFunc isSuitableFunc) const;

private:
    ParkingPlaces _freePlaces;
    ParkingPlaces _reservedPlaces;
};

} // namespace ParkingEngine

#endif /* ParkingPlacesManager_hpp */

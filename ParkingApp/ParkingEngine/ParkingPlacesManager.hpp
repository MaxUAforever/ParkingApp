#ifndef ParkingPlacesManager_hpp
#define ParkingPlacesManager_hpp

#include "ParkingPlace.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <map>

namespace ParkingEngine
{
using ParkingPlaces = std::map<PlaceIndex, ParkingPlace>;

class ParkingPlacesManager
{
public:
    ParkingPlacesManager(size_t placesCount);
    
    boost::optional<const ParkingPlace&> getPlace(PlaceIndex placeIndex) const;
    
    bool reserveFreePlace();
    bool reservePlace(PlaceIndex placeIndex);
    bool releasePlace(PlaceIndex placeIndex);
    
    bool isParkingFull() const;
    std::vector<PlaceIndex> getFreePlacesList() const;
    
private:
    ParkingPlaces _freePlaces;
    ParkingPlaces _reservedPlaces;
};

} // namespace ParkingEngine

#endif /* ParkingPlacesManager_hpp */

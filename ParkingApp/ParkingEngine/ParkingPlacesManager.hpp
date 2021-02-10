#ifndef ParkingPlacesManager_hpp
#define ParkingPlacesManager_hpp

#include "IParkingPlacesManager.hpp"
#include "ParkingPlace.hpp"
#include "Vehicle.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <map>
#include <set>

namespace ParkingEngine
{
using ParkingPlaces = std::map<PlaceID, ParkingPlace>;
using FreePlacesIDs = std::set<PlaceID>;
using ReservedPlacesIDs = std::map<EntryKeyID, PlaceID>;

using IsPlaceSuitableFunc = std::function<bool(const ParkingPlace&)>;

class ParkingPlacesManager : public IParkingPlacesManager
{
public:
    ParkingPlacesManager(size_t placesCount);
    
    boost::optional<const ParkingPlace&> getPlace(PlaceID placeID) const override;
    boost::optional<const ParkingPlace&> getReservedPlace(EntryKeyID keyID) const override;
    
    bool reserveFreePlace(EntryKeyID clientID) override;
    bool reservePlace(EntryKeyID clientID, PlaceID placeID) override;
    bool releasePlace(EntryKeyID clientID) override;
    
    bool isParkingFull() const override;
    std::vector<PlaceID> getFreePlacesList() const override;
    std::vector<PlaceID> getFreePlacesList(VehicleType vehicleType) const override;
    std::vector<PlaceID> getFreePlacesList(bool isForDisabledPerson) const override;
    
    void onSuccessPayment(EntryKeyID clientID) override;
    
private:
    std::vector<PlaceID> getFreePlacesListByParam(IsPlaceSuitableFunc isSuitableFunc) const;

private:
    ParkingPlaces _places;
    
    FreePlacesIDs _freePlaces;
    ReservedPlacesIDs _reservedPlaces;
};

} // namespace ParkingEngine

#endif /* ParkingPlacesManager_hpp */

#ifndef ParkingPlacesManager_hpp
#define ParkingPlacesManager_hpp

#include "IParkingPlacesManager.hpp"
#include "ParkingPlace.hpp"
#include "Vehicle.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <map>
#include <unordered_set>

namespace ParkingEngine
{
// TODO: change PlaceNumber to PlaceID;
// TODO: remove usings?
using ParkingPlaces = std::map<PlaceNumber, ParkingPlace>;
using FreePlacesIDs = std::unordered_set<PlaceNumber>;
using ReservedPlacesIDs = std::map<EntryKeyID, PlaceNumber>;

using IsPlaceSuitableFunc = std::function<bool(const ParkingPlace&)>;

class ParkingPlacesManager : public IParkingPlacesManager
{
public:
    ParkingPlacesManager(size_t placesCount);
    
    boost::optional<const ParkingPlace&> getPlace(PlaceNumber placeNumber) const override;
    boost::optional<const ParkingPlace&> getReservedPlace(EntryKeyID keyID) const override;
    
    bool reserveFreePlace(EntryKeyID clientID) override;
    bool reservePlace(EntryKeyID clientID, PlaceNumber placeNumber) override;
    bool releasePlace(EntryKeyID clientID) override;
    
    bool isParkingFull() const override;
    std::vector<PlaceNumber> getFreePlacesList() const override;
    std::vector<PlaceNumber> getFreePlacesList(VehicleType vehicleType) const override;
    std::vector<PlaceNumber> getFreePlacesList(bool isForDisabledPerson) const override;
    
    void onSuccessPayment(EntryKeyID clientID) override;
    
private:
    std::vector<PlaceNumber> getFreePlacesListByParam(IsPlaceSuitableFunc isSuitableFunc) const;

private:
    ParkingPlaces _places;
    
    FreePlacesIDs _freePlaces;
    ReservedPlacesIDs _reservedPlaces;
};

} // namespace ParkingEngine

#endif /* ParkingPlacesManager_hpp */

#ifndef ParkingPlacesManager_hpp
#define ParkingPlacesManager_hpp

#include "ISessionObserver.h"
#include "IParkingPlacesManager.hpp"
#include "ParkingPlace.hpp"
#include "SessionInfo.hpp"
#include "Vehicle.hpp"

#include <boost/optional.hpp>
#include <stdio.h>
#include <map>

namespace ParkingEngine
{
using ParkingPlaces = std::map<PlaceNumber, ParkingPlace>;
using IsPlaceSuitableFunc = std::function<bool(const ParkingPlace&)>;

class ParkingPlacesManager : public IParkingPlacesManager
{
public:
    ParkingPlacesManager(size_t placesCount);
    
    boost::optional<const ParkingPlace&> getPlace(PlaceNumber placeNumber) const override;
    
    bool reserveFreePlace() override;
    bool reservePlace(PlaceNumber placeNumber) override;
    bool releasePlace(PlaceNumber placeNumber) override;
    
    bool isParkingFull() const override;
    std::vector<PlaceNumber> getFreePlacesList() const override;
    std::vector<PlaceNumber> getFreePlacesList(VehicleType vehicleType) const override;
    std::vector<PlaceNumber> getFreePlacesList(bool isForDisabledPerson) const override;
    
    void onSuccessRelease(SessionInfo session) override;
    
private:
    std::vector<PlaceNumber> getFreePlacesListByParam(IsPlaceSuitableFunc isSuitableFunc) const;

private:
    ParkingPlaces _freePlaces;
    ParkingPlaces _reservedPlaces;
};

} // namespace ParkingEngine

#endif /* ParkingPlacesManager_hpp */

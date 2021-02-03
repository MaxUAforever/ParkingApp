#ifndef IParkingPlacesManager_hpp
#define IParkingPlacesManager_hpp

#include "ParkingPlace.hpp"
#include "ISessionObserver.h"

#include <boost/optional.hpp>

namespace ParkingEngine
{

class IParkingPlacesManager : public ISessionObserver
{
public:
    virtual ~IParkingPlacesManager() = default;
    
    virtual boost::optional<const ParkingPlace&> getPlace(PlaceNumber placeNumber) const = 0;
    
    virtual bool reserveFreePlace() = 0;
    virtual bool reservePlace(PlaceNumber placeNumber) = 0;
    virtual bool releasePlace(PlaceNumber placeNumber) = 0;
    
    virtual bool isParkingFull() const = 0;
    virtual std::vector<PlaceNumber> getFreePlacesList() const = 0;
    virtual std::vector<PlaceNumber> getFreePlacesList(VehicleType vehicleType) const = 0;
    virtual std::vector<PlaceNumber> getFreePlacesList(bool isForDisabledPerson) const = 0;
    
    virtual void onSuccessRelease(SessionInfo session) override = 0;
};

} // namespace ParkingEngine

#endif /* IParkingPlacesManager_hpp */

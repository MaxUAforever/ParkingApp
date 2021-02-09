#ifndef IParkingPlacesManager_hpp
#define IParkingPlacesManager_hpp

#include "EntryKeyGenerator.hpp"
#include "ParkingPlace.hpp"
#include "IPaymentObserver.h"

#include <boost/optional.hpp>

namespace ParkingEngine
{

class IBaseParkingPlacesManager
{
public:
    virtual ~IBaseParkingPlacesManager() = default;
    
    virtual boost::optional<const ParkingPlace&> getPlace(PlaceNumber placeNumber) const = 0;
    virtual boost::optional<const ParkingPlace&> getReservedPlace(EntryKeyID keyID) const = 0;
    
    virtual bool reserveFreePlace(EntryKeyID clientID) = 0;
    virtual bool reservePlace(EntryKeyID clientID, PlaceNumber placeNumber) = 0;
    virtual bool releasePlace(EntryKeyID clientID) = 0;
    
    virtual bool isParkingFull() const = 0;
    virtual std::vector<PlaceNumber> getFreePlacesList() const = 0;
    virtual std::vector<PlaceNumber> getFreePlacesList(VehicleType vehicleType) const = 0;
    virtual std::vector<PlaceNumber> getFreePlacesList(bool isForDisabledPerson) const = 0;
};

class IParkingPlacesManager : public IBaseParkingPlacesManager, public IPaymentObserver
{
};

} // namespace ParkingEngine

#endif /* IParkingPlacesManager_hpp */

#ifndef Parking_hpp
#define Parking_hpp

#include <stdio.h>
#include <map>
#include <unordered_map>
#include <vector>
#include <boost/variant.hpp>

#include "Barrier.hpp"
#include "Car.hpp"
#include "IBarrierObserver.hpp"
#include "ParkingPlace.hpp"
#include "Ticket.hpp"

namespace ParkingEngine
{

enum class AccessErrorCode : std::uint8_t
{
    FullParking,
    NotEmptyPlace,
    DuplicateCarNumber
};

using AccessResult = boost::variant<Ticket, AccessErrorCode>;

using ParkingPlaces = std::map<PlaceIndex, ParkingPlace>;
using Tickets = std::unordered_map<CarRegNumber, Ticket>;
using Barriers = std::vector<Barrier>;

class Parking : public IBarrierObserver
{
public:
    Parking(size_t placesCount, size_t barriersCount);

    AccessResult acceptCar(const Car& car, int barrierNumber);
    AccessResult acceptCar(const Car& car, int barrierNumber, size_t placeIndex);
    void releaseCar(const Car& car, int barrierNumber);

    void onAlert(size_t barrierIndex) override;
    
    std::vector<PlaceIndex> getFreePlacesList() const;
    
private:
    AccessResult reservePlace(const Car& car, ParkingPlaces::iterator placeIt);
    
private:
    Barriers _barriers;
    ParkingPlaces _freePlaces;
    Tickets _tickets;
};

} //namespace ParkingEngine

#endif /* Parking_hpp */

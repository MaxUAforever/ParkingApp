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
#include "PaymentManager.hpp"
#include "ParkingPlace.hpp"
#include "ParkingPlacesManager.hpp"
#include "Ticket.hpp"

namespace ParkingEngine
{
class PaymentManager;

enum class AccessErrorCode : std::uint8_t
{
    FullParking,
    NotEmptyPlace,
    DuplicateCarNumber
};

using AccessResult = boost::variant<Ticket, AccessErrorCode>;

using Cars = std::unordered_map<CarRegNumber, Car>;
using Tickets = std::unordered_map<CarRegNumber, Ticket>;
using Barriers = std::vector<Barrier>;

class Parking : public IBarrierObserver
{
public:
    Parking(size_t placesCount, size_t barriersCount);

    AccessResult acceptCar(const Car& car, size_t barrierNumber);
    AccessResult acceptCar(const Car& car, size_t barrierNumber, size_t placeNumber);
    void releaseCar(const Car& car, size_t barrierNumber);

    void onAlert(size_t barrierIndex) override;
    
    std::vector<PlaceNumber> getFreePlacesList() const;
    
private:
    void handleBarrierAlert(size_t barrierNumber);
    
    AccessResult reservePlace(const Car& car, PlaceNumber placeNumber);
    
private:
    PaymentManager _paymentManager;
    ParkingPlacesManager _placesManager;
    Barriers _barriers;
    Tickets _tickets;
    Cars _cars;
};

} //namespace ParkingEngine

#endif /* Parking_hpp */

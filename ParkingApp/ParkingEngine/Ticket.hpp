#ifndef Ticket_hpp
#define Ticket_hpp

#include <stdio.h>

#include "ParkingPlace.hpp"
#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{

class Ticket
{
public:
    explicit Ticket(EntryKeyID keyID, PlaceNumber placeNumber);

    EntryKeyID getKeyID() const;
    PlaceNumber getPlaceNumber() const;

private:
    EntryKeyID _keyID;
    PlaceNumber _placeNumber;
};

}

#endif /* Ticket_hpp */

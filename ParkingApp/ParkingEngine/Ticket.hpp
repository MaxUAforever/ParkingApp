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
    explicit Ticket(EntryKeyID keyID, PlaceID placeID);

    EntryKeyID getKeyID() const;
    PlaceID getPlaceID() const;

private:
    EntryKeyID _keyID;
    PlaceID _placeID;
};

}

#endif /* Ticket_hpp */

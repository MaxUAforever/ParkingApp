#include "Ticket.hpp"

namespace ParkingEngine
{

Ticket::Ticket(EntryKeyID keyID, PlaceNumber placeNumber)
    : _keyID(keyID)
    , _placeNumber(placeNumber)
{
}

EntryKeyID Ticket::getKeyID() const
{
    return _keyID;
}

PlaceNumber Ticket::getPlaceNumber() const
{
    return _placeNumber;
}

}

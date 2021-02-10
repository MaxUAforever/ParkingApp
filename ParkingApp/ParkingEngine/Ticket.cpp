#include "Ticket.hpp"

namespace ParkingEngine
{

Ticket::Ticket(EntryKeyID keyID, PlaceID placeID)
    : _keyID(keyID)
    , _placeID(placeID)
{
}

EntryKeyID Ticket::getKeyID() const
{
    return _keyID;
}

PlaceID Ticket::getPlaceID() const
{
    return _placeID;
}

} // namespace ParkingEngine

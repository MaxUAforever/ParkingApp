#include "Client.hpp"

namespace ParkingEngine
{

Client::Client(std::string name)
    : _clientID(EntryKeyGenerator::generateKey())
    , _name(std::move(name))
    , _discountSum(0)
{
}

EntryKeyID Client::getClientID() const
{
    return _clientID;
}

size_t Client::getDiscountSum() const
{
    return _discountSum;
}

void Client::setDiscountSum(size_t discountSum)
{
    _discountSum = discountSum;
}

void Client::addDiscountSum(size_t additionalSum)
{
    _discountSum += additionalSum;
}

} // namespace ParkingEngine

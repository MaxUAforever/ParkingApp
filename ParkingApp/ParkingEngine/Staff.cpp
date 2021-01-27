#include "Staff.hpp"

namespace ParkingEngine
{

Staff::Staff(std::string name)
    : _accessCode(EntryKeyGenerator::generateKey())
    , _name(std::move(name))
{
}

EntryKeyID Staff::getAccessCode()
{
    return _accessCode;
}

} // namespace ParkingEngine

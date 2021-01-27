#include "StaffManager.hpp"

namespace ParkingEngine
{

boost::optional<const Staff&> StaffManager::getStaff(EntryKeyID keyID) const
{
    auto staffIt = _staffs.find(keyID);
                            
    if (staffIt == _staffs.end())
    {
        return staffIt->second;
    }
    
    return boost::none;
}

void StaffManager::addStaff(std::string name)
{
    Staff staff(std::move(name));
    
    _staffs.emplace(staff.getAccessCode(), std::move(staff));
}

} // namespace ParkingEngine

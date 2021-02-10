#ifndef IStaffManager_hpp
#define IStaffManager_hpp

#include "Staff.hpp"

namespace ParkingEngine
{

class IStaffManager
{
public:
    virtual ~IStaffManager() = default;
    
    virtual boost::optional<const Staff&> getStaff(EntryKeyID keyID) const = 0;
    
    virtual void addStaff(std::string name) = 0;
};

} // namespace ParkingEngine

#endif /* IStaffManager_hpp */

#ifndef StaffManager_hpp
#define StaffManager_hpp

#include <boost/optional.hpp>
#include <stdio.h>
#include <unordered_map>

#include "Staff.hpp"

namespace ParkingEngine
{

class StaffManager
{
public:
    boost::optional<const Staff&> getStaff(EntryKeyID keyID) const;
    void addStaff(std::string name);
    
private:
    std::unordered_map<EntryKeyID, Staff> _staffs;
};

} // namespace ParkingEngine

#endif /* StaffManager_hpp */

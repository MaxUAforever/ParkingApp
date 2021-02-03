#ifndef StaffManager_hpp
#define StaffManager_hpp

#include <boost/optional.hpp>
#include <stdio.h>
#include <unordered_map>

#include "IStaffManager.hpp"

namespace ParkingEngine
{

class StaffManager : public IStaffManager
{
public:
    boost::optional<const Staff&> getStaff(EntryKeyID keyID) const override;
    void addStaff(std::string name) override;
    
private:
    std::unordered_map<EntryKeyID, Staff> _staffs;
};

} // namespace ParkingEngine

#endif /* StaffManager_hpp */

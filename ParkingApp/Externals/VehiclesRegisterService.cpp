#include "VehiclesRegisterService.hpp"

namespace ParkingEngine
{

boost::optional<bool> VehiclesRegisterService::checkIsVehicleForDisabled(std::string regNumber)
{
    static int crashCount = 0;
    
    if (crashCount == 3)
    {
        return false;
    }
    if (crashCount == 5)
    {
        return boost::none;
    }
    
    return true;
}

} // namespace ParkingEngine

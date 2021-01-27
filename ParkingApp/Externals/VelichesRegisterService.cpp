#include "VelichesRegisterService.hpp"

namespace Externals
{

boost::optional<bool> VelichesRegisterService::checkIsVehicleForDisabled(std::string regNumber)
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

} // namespace Externals

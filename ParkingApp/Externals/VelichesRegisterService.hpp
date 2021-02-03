#ifndef VelichesRegisterService_hpp
#define VelichesRegisterService_hpp

#include <stdio.h>
#include <string>
#include <boost/optional.hpp>

namespace ParkingEngine
{

class VelichesRegisterService
{
public:
    static boost::optional<bool> checkIsVehicleForDisabled(std::string regNumber);
};

} // namespace ParkingEngine

#endif /* VelichesRegisterService_hpp */

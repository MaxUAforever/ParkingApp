#ifndef VehiclesRegisterService_hpp
#define VehiclesRegisterService_hpp

#include <stdio.h>
#include <string>
#include <boost/optional.hpp>

namespace ParkingEngine
{

class VehiclesRegisterService
{
public:
    static boost::optional<bool> checkIsVehicleForDisabled(std::string regNumber);
};

} // namespace ParkingEngine

#endif /* VehiclesRegisterService_hpp */

#ifndef VelichesRegisterService_hpp
#define VelichesRegisterService_hpp

#include <stdio.h>
#include <string>
#include <boost/optional.hpp>

namespace Externals
{

class VelichesRegisterService
{
public:
    static boost::optional<bool> checkIsVehicleForDisabled(std::string regNumber);
};

} // namespace Externals
#endif /* VelichesRegisterService_hpp */

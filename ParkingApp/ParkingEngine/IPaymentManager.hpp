#ifndef IPaymentManager_hpp
#define IPaymentManager_hpp

#include <stdio.h>
#include <iostream>

namespace ParkingEngine
{
class SessionInfo;
class ParkingPlace;
enum class VehicleType : std::uint8_t;

class IPaymentManager
{
public:
    virtual ~IPaymentManager() = default;
    virtual size_t getTotalPrice(const SessionInfo& session, const ParkingPlace& place) const = 0;
    
    virtual void setVelicheCoefficient(VehicleType vehicleType, double vehicleCoefficient) = 0;

};

} // namespace ParkingEngine

#endif /* IPaymentManager_hpp */

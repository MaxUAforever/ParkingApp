#ifndef IBarriersManager_hpp
#define IBarriersManager_hpp

#include "Barrier.hpp"
#include "IBarrierObserver.hpp"

namespace ParkingEngine
{

class IBarriersManager
{
public:
    virtual ~IBarriersManager() = default;

    virtual bool openBarrier(size_t index) = 0;
    
    virtual void registerBarriersObserver(IBarrierObserver* observer) = 0;
};

} // namespace ParkingEngine

#endif /* IBarriersManager_hpp */

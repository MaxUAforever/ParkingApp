#ifndef BarriersManager_hpp
#define BarriersManager_hpp

#include <stdio.h>

#include "IBarriersManager.hpp"

namespace ParkingEngine
{
using Barriers = std::vector<Barrier>;

class BarriersManager : public IBarriersManager
{
public:
    explicit BarriersManager(size_t barriersCount);

    bool openBarrier(size_t index) override;
    
    void registerBarriersObserver(IBarrierObserver* observer) override;
    
private:
    Barriers _barriers;
};

} // namespace ParkingEngine

#endif /* BarriersManager_hpp */

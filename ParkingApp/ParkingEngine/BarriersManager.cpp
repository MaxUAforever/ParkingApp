#include "BarriersManager.hpp"

namespace ParkingEngine
{

BarriersManager::BarriersManager(const size_t barriersCount)
{
    _barriers.reserve(barriersCount);
    for (auto i = 1; i <= barriersCount; ++i)
    {
        _barriers.emplace_back(i);
    }
}

bool BarriersManager::openBarrier(size_t index)
{
    return _barriers.at(index).open();
}

void BarriersManager::registerBarriersObserver(IBarrierObserver *observer)
{
    for (auto& barrier : _barriers)
    {
        barrier.registerObserver(observer);
    }
}


} // namespace ParkingEngine

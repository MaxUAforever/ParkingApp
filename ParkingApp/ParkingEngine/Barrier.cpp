#include "Barrier.hpp"

Barrier::Barrier(size_t index)
    : _index(index)
{};

void Barrier::registerObserver(IBarrierObserver* observer)
{
    _observers.push_back(observer);
}

void Barrier::alert()
{
    for (auto observer : _observers)
    {
        observer->onAlert(_index);
    }
}

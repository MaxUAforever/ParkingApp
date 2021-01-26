#include "Barrier.hpp"

Barrier::Barrier(size_t index)
    : _index(index)
{};

void Barrier::registerObserver(IBarrierObserver* observer)
{
    _observers.push_back(observer);
}

bool Barrier::open()
{
    static int crashCount = 0;
    
    if (crashCount++ == 3)
    {
        alert();
        crashCount = 0;
        
        return false;
    }
    
    return true;
}

void Barrier::callAlert()
{
    alert();
}

void Barrier::alert()
{
    for (auto observer : _observers)
    {
        observer->onAlert(_index);
    }
}

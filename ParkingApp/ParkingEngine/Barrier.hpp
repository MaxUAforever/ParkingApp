#ifndef Barrier_hpp
#define Barrier_hpp

#include <stdio.h>
#include <vector>

#include "IBarrierObserver.hpp"

class Barrier
{
public:
    explicit Barrier(size_t index);
    
    void registerObserver(IBarrierObserver* observer);
    
    bool open();
    void alert();
    
private:
    size_t _index;
    
    std::vector<IBarrierObserver*> _observers;
};

#endif /* Barrier_hpp */

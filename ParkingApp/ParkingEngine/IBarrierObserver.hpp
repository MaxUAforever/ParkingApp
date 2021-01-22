#ifndef IBarrierObserver_hpp
#define IBarrierObserver_hpp

class IBarrierObserver
{
public:
    virtual ~IBarrierObserver() = default;
    
    virtual void onAlert(size_t barrierIndex) = 0;
};

#endif /* IBarrierObserver_hpp */

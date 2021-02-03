#ifndef ISessionObserver_h
#define ISessionObserver_h

namespace ParkingEngine
{
class SessionInfo;

class ISessionObserver
{
public:
    virtual ~ISessionObserver() = default;
    
    virtual void onSuccessRelease(SessionInfo session) = 0;
};

} // namespace ParkingEngine

#endif /* ISessionObserver_h */

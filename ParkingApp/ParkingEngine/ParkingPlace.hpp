#ifndef ParkingPlace_hpp
#define ParkingPlace_hpp

#include <stdio.h>

namespace ParkingEngine
{

class ParkingPlace
{
public:
    explicit ParkingPlace(size_t number);
    
    const size_t getNumber() const;
    
    bool operator== (const ParkingPlace& place) const;
    
private:
    size_t _number;
};

} // namespace ParkingEngine

#endif /* ParkingPlace_hpp */

#ifndef ParkingPlace_hpp
#define ParkingPlace_hpp

#include <stdio.h>

namespace ParkingEngine
{
using PlaceIndex = size_t;

class ParkingPlace
{
public:
    explicit ParkingPlace(PlaceIndex number);
    
    PlaceIndex getNumber() const;
    size_t getPrice() const;
    
    bool operator== (const ParkingPlace& place) const;
    bool operator< (const ParkingPlace& place) const;
    
private:
    PlaceIndex _number;
    size_t _price;
};

} // namespace ParkingEngine

#endif /* ParkingPlace_hpp */

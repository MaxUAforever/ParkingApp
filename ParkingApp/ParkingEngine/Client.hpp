#ifndef Client_hpp
#define Client_hpp

#include "EntryKeyGenerator.hpp"

#include <stdio.h>
#include <string>

namespace ParkingEngine
{
class Client
{
public:
    explicit Client(std::string name);

    EntryKeyID getClientID() const;

    size_t getDiscountSum() const;
    void setDiscountSum(size_t discountSum);
    void addDiscountSum(size_t additionalSum);
    
private:
    EntryKeyID _clientID;
    std::string _name;
    size_t _discountSum;
};

} // namespace ParkingEngine

#endif /* Client_hpp */

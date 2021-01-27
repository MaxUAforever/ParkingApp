#ifndef EntryKeyGenerator_hpp
#define EntryKeyGenerator_hpp

#include <stdio.h>

namespace ParkingEngine
{
using EntryKeyID = int;

class EntryKeyGenerator
{
public:
    static EntryKeyID generateKey();
};

} // namespace ParkingEngine

#endif /* EntryKeyGenerator_hpp */

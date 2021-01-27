#include "EntryKeyGenerator.hpp"

namespace ParkingEngine
{

EntryKeyID EntryKeyGenerator::generateKey()
{
    static EntryKeyID key = 0;
    
    return key++;
}

} // namespace ParkingEngine

#include "PaymentService.hpp"

#include <iostream>

bool PaymentService::getPayment(size_t amount)
{
    size_t userAmount = 0;
    size_t attemptsCount = 5;
    
    while (userAmount != amount)
    {
        userAmount = amount;
        
        std::cout << "Enter the amount to confirm (" << amount << ") or enter '0' to discard: ";
        std::cout << userAmount;
        std::cout << std::endl;
        
        if (userAmount != amount)
        {
            --attemptsCount;
        }
        
        if (attemptsCount == 0 || userAmount == 0)
        {
            return false;
        }
    }
    
    return true;
}

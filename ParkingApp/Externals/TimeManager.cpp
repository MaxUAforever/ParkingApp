#include "TimeManager.hpp"

static size_t currentTime = 0;

size_t TimeManager::getCurrentTime()
{
    return ++currentTime;
}

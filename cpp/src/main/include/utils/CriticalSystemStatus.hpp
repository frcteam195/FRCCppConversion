#pragma once

#include <stdbool.h>

class CriticalSystemStatus {
public:
    virtual bool isSystemFaulted() = 0;
};
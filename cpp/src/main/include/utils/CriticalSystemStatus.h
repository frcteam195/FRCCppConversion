#pragma once

#include <stdbool.h>

class CriticalSystemStatus {
public:
    virtual bool IsSystemFaulted() = 0;
};
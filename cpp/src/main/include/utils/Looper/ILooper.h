#pragma once

#include "Loop.h"

class ILooper {
public:
    virtual void Register(Loop & loop);
};
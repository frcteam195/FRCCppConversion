#pragma once

#include <string>

class Loop {
public:
    virtual void OnFirstStart(double timestamp) = 0;
    virtual void OnStart(double timestamp) = 0;
    virtual void OnStop(double timestamp) = 0;
    virtual void OnLoop(double timestamp) = 0;
    virtual std::string GetName() = 0;
};
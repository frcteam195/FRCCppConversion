#include <string>

class Loop {
public:
    virtual void OnFirstStart(double timestamp);
    virtual void OnStart(double timestamp);
    virtual void OnStop(double timestamp);
    virtual void OnLoop(double timestamp);
    virtual std::string GetName();
};
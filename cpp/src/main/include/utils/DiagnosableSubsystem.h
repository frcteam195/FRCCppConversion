#include <stdbool.h>

class DiagnosableSubsystem {
public:
    virtual bool RunDiagnostics() = 0;
};
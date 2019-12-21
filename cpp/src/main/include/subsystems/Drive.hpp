#pragma once

#include "ctre/Phoenix.h"
#include "utils/Subsystem.hpp"

class Drive : public Subsystem {
public:
    static Drive* getInstance();

    void stop() override;

    bool isSystemFaulted() override;

    bool runDiagnostics() override;

    std::vector<void*> generateReport() override;

private:
    Drive();

    static Drive* mInstance;
};

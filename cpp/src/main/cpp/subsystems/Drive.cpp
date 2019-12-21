#include "subsystems/Drive.hpp"

Drive* Drive::mInstance;

Drive::Drive() {}

Drive* Drive::getInstance() {
    if (!mInstance) {
        mInstance = new Drive();
    }

    return mInstance;
}

void Drive::stop() {

}

bool Drive::isSystemFaulted() {
    return false;
}

bool Drive::runDiagnostics() {
    return true;
}

std::vector<void*> Drive::generateReport() {
    throw ">:(";
}

#include "subsystems/Drive.hpp"

Drive* Drive::mInstance = new Drive();

Drive::Drive() {}

Drive* Drive::getInstance() {
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

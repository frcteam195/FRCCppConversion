#include "subsystems/Drive.hpp"

DataReporter* Drive::logReporter = &NetworkDataReporter::getInstance();

Drive::Drive() {

}

void Drive::stop() {

}

void Drive::onFirstStart(double timestamp) {

}

void Drive::onStart(double timestamp) {

}

void Drive::onStop(double timestamp) {
    stop();
}

void Drive::onLoop(double timestamp) {
    
}

std::string Drive::getName() {
    return "DriveLoop";
}

void Drive::registerEnabledLoops(ILooper & enabledLooper) {
    enabledLooper.registerLoop(*this);
}

bool Drive::isSystemFaulted() {
    return false;
}

bool Drive::runDiagnostics() {
    return true;
}

Drive::PeriodicIO::PeriodicIO()
:DECLARE_REPORTED(logReporter,left_position_rotations)
,DECLARE_REPORTED(logReporter,right_position_rotations)
{
    // left_position_rotations = 3;
    // right_position_rotations = 4;
}
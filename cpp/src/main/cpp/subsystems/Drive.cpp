#include "subsystems/Drive.hpp"

DataReporter* Drive::logReporter = &NetworkDataReporter::getInstance();

Drive::Drive() {

}

void Drive::stop() {

}

void Drive::DriveLoop::onFirstStart(double timestamp) {

}

void Drive::DriveLoop::onStart(double timestamp) {

}

void Drive::DriveLoop::onStop(double timestamp) {

}

void Drive::DriveLoop::onLoop(double timestamp) {
    
}

std::string Drive::DriveLoop::getName() {
    return "DriveLoop";
}

void Drive::registerEnabledLoops(ILooper & enabledLooper) {
    enabledLooper.registerLoop(mDriveLoop);
}

bool Drive::isSystemFaulted() {
    return false;
}

bool Drive::runDiagnostics() {
    return true;
}

Drive::PeriodicIO::PeriodicIO()
:DECLARE_REPORTED(left_position_rotations)
,DECLARE_REPORTED(right_position_rotations)
{
    // left_position_rotations = 3;
    // right_position_rotations = 4;
}
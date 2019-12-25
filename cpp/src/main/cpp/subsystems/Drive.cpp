#include "subsystems/Drive.hpp"

DataReporter* Drive::logReporter = &NetworkDataReporter::getInstance();

Drive::Drive() {

}

void Drive::stop() {

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
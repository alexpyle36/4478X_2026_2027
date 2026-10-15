#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"
#include "devices.hpp"

using namespace pros;

void initialize() {
    buttons.suspend();
    headingWrap.suspend();
    findObject.suspend();
    impactCorrection.suspend();
    poseReset.suspend();
    chassis.calibrate(); // calibrate sensors
}
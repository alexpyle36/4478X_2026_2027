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

void headingDisp_fn() {
    while (true) {
        master.print(0, 0, "X: %.2f", chassis.getPose().x);
        master.print(1, 0, "Y: %.2f", chassis.getPose().y);
        master.print(2, 0, "Theta: %.2f", chassis.getPose().theta);
        delay(100);
    }
}

Task headingDisp(headingDisp_fn);

void initialize_fn() {
    lcd::initialize();
    buttons.suspend();
    headingWrap.resume();
    impactCorrection.suspend();
    findObject.suspend();
    poseReset.suspend();
    chassis.calibrate(); // calibrate sensors
    headingDisp.resume();
    claw.set_value(false);
}
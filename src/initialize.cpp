#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "distance.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"
#include "devices.hpp"
#include "pros/abstract_motor.hpp"

using namespace pros;

void headingDisp_fn() {
    while (true) {
        master.print(0, 0, "Theta: %.2f", chassis.getPose().theta);
        delay(100);
    }
}

void overheatedDisp_fn() {
    int overheated = 0;
    while (true) {
        if ((cascadeMotorGroup.is_over_temp(0) == 1) || (cascadeMotorGroup.is_over_temp(1) == 1)) {
            overheated += 1;
        }
        if (left_mg.is_over_temp(0) == 1 || left_mg.is_over_temp(1) == 1 || right_mg.is_over_temp(0) == 1 || right_mg.is_over_temp(1) == 1) {
            overheated += 2;
        }
        switch (overheated) {
            case 0:
                master.print(0, 0, "Heated: %.2f", "None");
                break;
            case 1:
                master.print(0, 0, "Heated: %.2f", "Cascade");
                break;
            case 2:
                master.print(0, 0, "Heated: %.2f", "Drive");
                break;
            case 3:
                master.print(0, 0, "Heated: %.2f", "All");
                break;
        }
        delay(100);
    }
}

Task headingDisp(headingDisp_fn);
Task overheatedDisp(overheatedDisp_fn);

void initialize_fn() {
    lcd::initialize();
    buttons.suspend();
    impactCorrection.suspend();
    findObject.suspend();
    poseReset.suspend();
    overheatedDisp.suspend();
    chassis.calibrate(); // calibrate sensors
    headingDisp.resume();
    headingWrap.resume();
    claw.set_value(false);
    cascade.reset();
    cascadeMotorGroup.set_brake_mode_all(MotorBrake::hold);
}
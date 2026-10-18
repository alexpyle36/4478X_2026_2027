#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "distance.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"
#include "devices.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/llemu.hpp"

using namespace pros;

void headingDisp_fn() {
    while (true) {
        lcd::print(1, "Theta: %.2f", chassis.getPose().theta);
        delay(20);
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
                master.print(2, 0, "Heated: None");
                break;
            case 1:
                master.print(2, 0, "Heated: Cascade");
                break;
            case 2:
                master.print(2, 0, "Heated: Drive");
                break;
            case 3:
                master.print(2, 0, "Heated: All");
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
    headingDisp.resume();
    headingWrap.resume();
    chassis.calibrate(); // calibrate sensors
    claw.set_value(false);
    cascade.reset();
    cascadeMotorGroup.set_brake_mode_all(MotorBrake::hold);
}
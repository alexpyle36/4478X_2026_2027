#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "distance.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"
#include "devices.hpp"

using namespace pros;

void headingDisp_fn() {
    while (true) {
        lcd::print(1, "Theta: %.2f", chassis.getPose().theta);
        delay(20);
    }
}

double expectedHeading = 0;
double expectedDistance = 0;

void headingErrorDisp_fn() {
    while (true) {
        lcd::print(2, "Error: %.2f", chassis.getPose().theta - expectedHeading);
        delay(20);
    }
}

void distanceErrorDisp_fn() {
    while (true) {
        lcd::print(2, "Error: %.2f", chassis.getPose().y - expectedDistance);
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
Task headingErrorDisp_task(headingErrorDisp_fn);
Task distanceErrorDisp_task(distanceErrorDisp_fn);

void headingErrorDisp(double expected) {
    expectedHeading = expected;
    headingErrorDisp_task.resume();
}

void distanceErrorDisp(double expected) {
    expectedHeading = expected;
    distanceErrorDisp_task.resume();
}

void initialize_fn() {
    lcd::initialize();
    buttons.suspend();
    impactCorrection.suspend();
    findObject.suspend();
    poseReset.suspend();
    overheatedDisp.suspend();
    headingErrorDisp_task.suspend();
    headingDisp.resume();
    headingWrap.resume();
    chassis.calibrate(); // calibrate sensors
    claw.setClaw(Claw::CLOSED);
    cascade.setZeroPos();
}
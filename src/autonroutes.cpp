#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "functions.hpp"
#include "devices.hpp"

using namespace pros;

// Skills auton route
void skillsAuton() {
	headingWrap.resume();
    chassis.setPose(0, 0, 0);
	headingWrap.suspend();
}

void nonLemlibMainSideAuton() {
	headingWrap.resume();
	cascadeMotorGroup.move(200);
	delay(1000);
	cascadeMotorGroup.brake();
	left_mg.move_relative(-1.2, 300);
	right_mg.move_relative(-1.2, 300);
	delay(500);
	left_mg.move_relative(0.5, 300);
	right_mg.move_relative(0.5, 300);
	delay(1000);
	left_mg.move_relative(-1, 200);
	right_mg.move_relative(-1, 200);
	delay(400);
	left_mg.move_relative(3.2, 200);
	right_mg.move_relative(3.2, 200);
	delay(620);
	left_mg.move_relative(1.3, 200);
	right_mg.move_relative(-1.3, 200);
	delay(800);
	left_mg.move_relative(2.6, 200);
	right_mg.move_relative(2.6, 200);
	delay(1400);
	cascade.score(10);
	delay(1000);
	claw.set_value(true);
	delay(500);
	left_mg.move_relative(-1.3, 200);
	right_mg.move_relative(-1.3, 200);
	headingWrap.suspend();
}

// Main side auton route
void mainSideAuton() {
    headingWrap.resume();
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0, -10, 1000, {.forwards = false});
	chassis.setPose(0, -2, chassis.getPose().theta);
	chassis.moveToPoint(0, 0, 500);
	chassis.moveToPoint(0, -10, 2000, {.forwards = false});
    chassis.setPose(0, -2, chassis.getPose().theta);
	chassis.moveToPoint(0, 16, 2000);
	chassis.turnToPoint(23.5, 16, 3000);
	chassis.moveToPoint(16, 16, 2000);
	//cascade.score(100);
	chassis.moveToPoint(20, 16, 2000);
	claw.set_value(true);
	chassis.moveToPoint(16, 16, 2000, {.forwards = false});
	//cascade.reset();
	chassis.moveToPoint(0, 16, 2000);
	headingWrap.suspend();
}

// Right side auton route
void rightSideAuton() {
    headingWrap.resume();
    chassis.setPose(0, 0, 0);
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0, 16, 2000);
	chassis.turnToPoint(-23.5, 16, 3000);
	chassis.moveToPoint(-16, 16, 2000);
	headingWrap.suspend();
}

// AWP auton route
void AWPAuton() {
    headingWrap.resume();
    chassis.setPose(0, 0, 0);
	headingWrap.suspend();
}
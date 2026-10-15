#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"
#include "functions.hpp"
#include "devices.hpp"

using namespace pros;

// Skills auton route
void skillsAuton() {
	headingWrap.resume();
    chassis.setPose(0, 0, 0);
	headingWrap.suspend();
}

// Main side auton route
void mainSideAuton() {
    headingWrap.resume();
    chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0, 16, 2000);
	chassis.turnToPoint(23.5, 16, 3000);
	chassis.moveToPoint(16, 16, 2000);
	
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
#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"

using namespace pros;


// Wraps the robots heading around if it goes above 360 or below 0
void headingWrap_fn() {
	while (true) {
		if (chassis.getPose().theta < 0) chassis.setPose(chassis.getPose().x, chassis.getPose().y, (chassis.getPose().theta + 360));
		else if (chassis.getPose().theta > 360) chassis.setPose(chassis.getPose().x, chassis.getPose().y, (chassis.getPose().theta - 360));
		// delay to save resources
		delay(20);
	}
}

// Task for wraping the heading value between 360 and 0
Task headingWrap(headingWrap_fn);

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
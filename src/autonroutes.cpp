#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "functions.hpp" // IWYU pragma: keep
#include "devices.hpp"
#include "initialize.hpp" // IWYU pragma: keep
#include "pros/motors.h"

using namespace pros;

// Skills auton route - Not Finished or tested
void skillsAuton() {
	cascade.move();
	delay(1000);
	
	cascade.brake();
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
	claw.setClaw(Claw::OPEN);
	delay(500);
	left_mg.move_relative(-1.3, 200);
	right_mg.move_relative(-1.3, 200);
	delay(2000);
	chassis.turnToPoint(23.5, 40, 3000);
	chassis.turnToPoint(23.5, 40, 1000);
	chassis.moveToPoint(23.5, 40, 7000, {.maxSpeed = 31.75});
	claw.setClaw(Claw::CLOSED);
	delay(500);
	cascadeMotorGroup.move(200);
	delay(1000);
	cascadeMotorGroup.brake();
	chassis.turnToHeading(180, 2000);
	chassis.turnToHeading(180, 2000);
	delay(2000);
	left_mg.move_relative(2.6, 200);
	right_mg.move_relative(2.6, 200);
	delay(1400);
	cascade.score(10);
	delay(1000);
	claw.setClaw(Claw::OPEN);
	delay(500);
	left_mg.move_relative(-1.3, 200);
	right_mg.move_relative(-1.3, 200);
	delay(2000);
	left_mg.move_relative(1.3, 200);
	right_mg.move_relative(-1.3, 200);
	delay(800);
	left_mg.move_relative(-4, 200);
	right_mg.move_relative(-4, 200);	
}

void fullSkills() {
	chassis.setPose(0, 9, 0);
	cascade.score(20);
	chassis.moveToPoint(48, 24, 3000, {.maxSpeed = 75});
	chassis.waitUntilDone();
	cascade.score(10);
	delay(1500);
	claw.setClaw(Claw::OPEN);
	delay(300);
	chassis.moveToPoint(0, 24, 3000, {.forwards = false});
	chassis.waitUntil(20);
	cascade.score(0);
	chassis.waitUntilDone();
	chassis.moveToPose(0, 7, 180, 2000);
	claw.setClaw(Claw::CLOSED);
	delay(300);
	chassis.moveToPoint(0, 24, 3000, {.forwards = false, .maxSpeed = 75});
	chassis.waitUntilDone();
	cascade.score(30);
	chassis.turnToPoint(48, 24, 1000);
	chassis.moveToPoint(48, 24, 2000, {.maxSpeed = 75});
	chassis.waitUntilDone();
	cascade.score(15);
	delay(1500);
	claw.setClaw(Claw::OPEN);
	/*chassis.moveToPoint(10, 74, 5000, {.maxSpeed = 60});
	chassis.waitUntilDone();
	cascade.score(10);
	delay(1500);
	claw.setClaw(Claw::OPEN);
	delay(200);
	chassis.moveToPoint(10, 64, 1000, {.forwards = false});
	chassis.waitUntilDone();
	chassis.moveToPoint(0, 0, 5000, {.maxSpeed = 30});*/
	//*/
}

// Basic auton route - Finished and tested
void baseAuton() {
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
	claw.setClaw(Claw::CLOSED);
	delay(500);
	left_mg.move_relative(-1.3, 200);
	right_mg.move_relative(-1.3, 200);
}

// Main side auton route - Finished but not tested
void leftAuton() {
	chassis.moveToPoint(0, -5, 1000, {.forwards = false});
    chassis.setPose(0, 0, chassis.getPose().theta);
	chassis.moveToPoint(0, 20, 2000);
	chassis.setPose(chassis.getPose().x, 23.5, chassis.getPose().theta);
	chassis.turnToPoint(23.5, 23.5, 3000);
	cascade.score(720);
	chassis.moveToPoint(23.5, 23.5, 2000);
	claw.setClaw(Claw::CLOSED);
	chassis.moveToPoint(0, 23.5, 2000, {.forwards = false});
	cascade.score(20);
	chassis.turnToPoint(23.5, 47, 1000);
	chassis.moveToPoint(23.5, 47, 3000);
	claw.setClaw(Claw::OPEN);
	cascade.score(720);
}

// Right side auton route - Not tested
void rightAuton() {
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
	left_mg.move_relative(-1.3, 200);
	right_mg.move_relative(1.3, 200);
	delay(800);
	left_mg.move_relative(2.6, 200);
	right_mg.move_relative(2.6, 200);
	delay(1400);
	cascade.score(10);
	delay(1000);
	claw.setClaw(Claw::CLOSED);
	delay(500);
	cascade.score(360);
	delay(500);
	left_mg.move_relative(-1.3, 200);
	right_mg.move_relative(-1.3, 200);
}

// AWP auton route - Not finished or tested
void AWPAuton() {
    
}

void autonRoute(autonroute route) {
	switch (route) {
		case Skills:
			skillsAuton();
			break;
		case FullSkills:
			fullSkills();
			break;
		case Base:
			baseAuton();
			break;
		case Left:
			leftAuton();
			break;
		case Right:
			rightAuton();
			break;
		case AWP:
			AWPAuton();
			break;
	};
}
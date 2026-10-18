#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "devices.hpp"
#include "functions.hpp" // IWYU pragma: keep
#include "pid.hpp"

using namespace pros;

void PID_tuning(PID type) {
	chassis.setPose(0, 0, 0);
	switch (type) {
		case LATERAL:
    		chassis.moveToPoint(0, 24, 100000);
			break;
		case ANGULAR:
    		chassis.turnToHeading(180, 100000);
			break;
		case ALL:
			chassis.moveToPoint(0, 24, 100000);
			chassis.turnToHeading(90, 100000);
			chassis.moveToPoint(24, 24, 100000);
			chassis.turnToHeading(180, 100000);
			chassis.moveToPoint(24, 0, 100000);
			chassis.turnToHeading(270, 100000);
			chassis.moveToPoint(0, 0, 100000);
			chassis.turnToHeading(0, 100000);
			break;
	}
	
}

/*// angular autoTune variables
double angular_kP = 3;
double angular_kI = 0;
double angular_kD = 10;
bool isAngularMotion = false;
bool angularIsOscillating = false;

// lateral autoTune variables
double lateral_kP = 10;
double lateral_kI = 0;
double lateral_kD = 3;
bool isLateralMotion = false;
bool lateralIsOscillating = false;

void autoTune() {
	if (isAngularMotion) {
		angular_controller.kI = 0;
		angular_controller.kD = 0;
		angular_controller.windupRange = 0;
		angular_controller.smallError = 0;
		angular_controller.smallErrorTimeout = 0;
		angular_controller.largeError = 0;
		angular_controller.largeErrorTimeout = 0;
		angular_controller.slew = 0;

		
	} else if (isLateralMotion) {
		lateral_controller.kI = 0;
		lateral_controller.kD = 0;
		lateral_controller.windupRange = 0;
		lateral_controller.smallError = 0;
		lateral_controller.smallErrorTimeout = 0;
		lateral_controller.largeError = 0;
		lateral_controller.largeErrorTimeout = 0;
		lateral_controller.slew = 0;


	}

}*/
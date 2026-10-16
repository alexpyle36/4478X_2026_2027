#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "devices.hpp"
#include "distance.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"
#include "pid.hpp"
#include "pneumatics.hpp"

using namespace pros;

void PID_tuning(PID type) {
	chassis.setPose(0, 0, 0);
	switch (type) {
		case LATERAL:
    		chassis.moveToPoint(0, 24, 100000);
			break;
		case ANGULAR:
			headingWrap.resume();
    		chassis.turnToHeading(90, 100000);
			headingWrap.suspend();
			break;
		case ALL:
			headingWrap.resume();
			chassis.moveToPoint(0, 24, 100000);
			chassis.turnToHeading(90, 100000);
			chassis.moveToPoint(24, 24, 100000);
			chassis.turnToHeading(180, 100000);
			chassis.moveToPoint(24, 0, 100000);
			chassis.turnToHeading(270, 100000);
			chassis.moveToPoint(0, 0, 100000);
			chassis.turnToHeading(0, 100000);
			headingWrap.suspend();
			break;
	}
}
#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"
#include "devices.hpp"
#include "functions.hpp"

using namespace pros;

// wraps a value around a min and max value
void wrap(double value, double min, double max) {
	if (value < min) value = max;
	else if (value > max) value = min;
}

bool lastInMotion = false;
lemlib::Pose lastPose = chassis.getPose();

// resets the pose of the robot to the last pose when it was not moving
void poseReset_fn() {
	while (true) {
		if (!chassis.isInMotion() && lastInMotion) {
			chassis.setPose(chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
			lastPose = chassis.getPose();
			lastInMotion = false;
		} else if (chassis.isInMotion()) {
			lastInMotion = true;
		} else {
			lastInMotion = false;
			chassis.setPose(lastPose.x, lastPose.y, lastPose.theta);
		}
		// delay to save resources
		delay(20);
	}
}

// wraps the heading around if it goes above 360 or below 0
void headingWrap_fn() {
	while (true) {
		wrap(chassis.getPose().theta, 0, 360);
		wrap(lastPose.theta, 0, 360);
		// delay to save resources
		delay(20);
	}
}

void impactCorrection_fn() {
	while (true) {
		if (chassis.getPose().theta > lastPose.theta + 5 || chassis.getPose().theta < lastPose.theta - 5) {
			chassis.cancelMotion();
			chassis.turnToHeading(lastPose.theta, 100000);
		}
		delay(20);
	}
}

// Task for wraping the heading value between 360 and 0
Task headingWrap(headingWrap_fn);
// Task for resetting the pose of the robot to the last pose when it was not moving
Task poseReset(poseReset_fn);
// Task for correcting the pose of the robot when it hits an obstacle and the heading changes drastically
Task impactCorrection(impactCorrection_fn);
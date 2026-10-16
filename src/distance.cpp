#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include <math.h>
#include "distance.hpp"
#include <algorithm> // IWYU pragma: keep
#include "devices.hpp"

using namespace pros;

void findObject_fn() {
	bool objectDetected = false;
	while (true) {
		if (front_sensor.get_object_size() > 100 && front_sensor.get_object_size() < 200) {
			chassis.cancelMotion();
			objectDetected = true;
			break;
		}
		else {
			objectDetected = false;
		}
		delay(20);
	}
}

Task findObject(findObject_fn);

void turnToFind(float aproxTheta) {
	findObject.resume();
	chassis.turnToHeading(aproxTheta - 15, 2000);
	chassis.turnToHeading(aproxTheta, 2000);
	chassis.turnToHeading(aproxTheta + 15, 2000);
	chassis.turnToHeading(aproxTheta, 2000);
	findObject.suspend();
}
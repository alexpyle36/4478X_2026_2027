#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include <math.h>
#include "distance.hpp"
#include <algorithm> // IWYU pragma: keep

using namespace pros;

// Master controller
Controller master(E_CONTROLLER_MASTER);
// Left motor group
MotorGroup left_mg({-1, -2, -3}, MotorGearset::blue);
// Right motor group
MotorGroup right_mg({4, 5, 6}, MotorGearset::blue);
// Drivetrain settings
lemlib::Drivetrain drivetrainSettings(&left_mg,
							  &right_mg,
							  1, // temporary
							  lemlib::Omniwheel::NEW_325,
							  450,
							  2 // temporary
);
// Imu
Imu imu(7);
// Vertical tracking wheel encoder
Rotation vertical_sensor(8);
// Horizontal tracking wheel encoder
Rotation horizontal_sensor(9);
// Front distance sensor
Distance front_sensor(12);
// Vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_sensor,
											  lemlib::Omniwheel::NEW_2,
											  1 // temporary
);
// Horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor,
											    lemlib::Omniwheel::NEW_2,
											    1 // temporary
);

// Odometry settings
lemlib::OdomSensors odomSensors(&vertical_tracking_wheel,
								nullptr,
								&horizontal_tracking_wheel,
								nullptr,
								&imu
);

// Lateral PID controller
lemlib::ControllerSettings lateral_controller(10,
											  0,
											  3,
											  3,
											  1,
											  100,
											  3,
											  500,
											  20
);

// Angular PID controller
lemlib::ControllerSettings angular_controller(2,
											  0,
											  10,
											  0,
											  0,
											  0,
											  0,
											  0,
											  0
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // Out of 127
                                      10, // Out of 127
                                      3
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // Out of 127
                                   10, // Out of 127
                                   3
);

// Chassis settiings
lemlib::Chassis chassis(drivetrainSettings,
						lateral_controller,
						angular_controller,
						odomSensors,
						&throttle_curve,
						&steer_curve
);

bool objectDetected;

void findObject_fn() {
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

Task findObject(findFrontObject_fn);

void turnToFind(float aproxTheta) {
	findObject.resume();
	chassis.turnToHeading(aproxTheta - 15, 2000);
	chassis.turnToHeading(aproxTheta, 2000);
	chassis.turnToHeading(aproxTheta + 15, 2000);
	chassis.turnToHeading(aproxTheta, 2000);
	findObject.suspend();
}
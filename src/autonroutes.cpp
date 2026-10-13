#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"

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
// First extra motor
Motor extraMotor1(10, MotorGearset::green);
// Second extra motor
Motor extraMotor2(11, MotorGearset::green);
// First pneumatic
adi::DigitalOut pneumatic1('A');
// Second pneumatic
adi::DigitalOut pneumatic2('B');
// Third pneumatic
adi::DigitalOut pneumatic3('C');
// Front distance sensor
Distance front_sensor(12);
// Right distance sensor
Distance right_sensor(13);
// Left distance sensor
Distance left_sensor(14);
// Back distance sensor
Distance back_sensor(15);
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

// Input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // Out of 127
                                      10, // Out of 127
                                      1.015
);

// Input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(4, // Out of 127
                                   12, // Out of 127
                                   1.08
);

// Chassis settiings
lemlib::Chassis chassis(drivetrainSettings,
						lateral_controller,
						angular_controller,
						odomSensors,
						&throttle_curve,
						&steer_curve
);
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
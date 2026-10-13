#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"
#include "autonroutes.hpp"
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"

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
// First pneumatic
adi::DigitalOut pneumatic1('A');
// Second pneumatic
adi::DigitalOut pneumatic2('B');
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
                                      12, // Out of 127
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

// Task for handling the controller butons
Task buttons(buttons_fn);
// Task for wraping the heading value between 360 and 0
Task headingWrap(headingWrap_fn);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	lcd::initialize();
	buttons.suspend();
	headingWrap.suspend();
	chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    Task screen_task([&]() {
       	while (true) {
           	// print robot location to the brain screen
           	lcd::print(0, "X: %f", chassis.getPose().x); // x
           	lcd::print(1, "Y: %f", chassis.getPose().y); // y
           	lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
			lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
           	// delay to save resources
           	delay(20);
       	}
    });
	//Task localization(localization_fn);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	headingWrap.resume();
    PID_tuning(PID::ANGULAR);
	headingWrap.suspend();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	buttons.resume();
	// Loops until broken by controller or competition control
	while (true) {
		// Left y axis controler position
		int leftY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		// Right y axis controler position
		int rightY = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		
		// Move the robot based of of inputs from the controlers left and right y axis position
		chassis.tank(leftY, rightY);

		// 20 msec delay to save resources
		delay(20);
	}
	buttons.suspend();
}
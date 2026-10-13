#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"
#include "pros/abstract_motor.hpp"

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
MotorGroup cascade({10, 11}, MotorGearset::blue);
// First pneumatic
adi::DigitalOut claw('A');
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

enum class Height{
	ONE,
	TWO,
	THREE,
	FOUR,
};

class Cascade{
	void score(Height height) {
		double h;
		if (height == Height::ONE) h = 1;
		else if (height == Height::TWO) h = 2;
		else if (height == Height::THREE) h = 3;
		else if (height == Height::THREE) h = 4;
		cascadePID(h);
	}
	void reset() {
		cascade.move_absolute(0, 300);
	}
};


void headingWrap_fn() {
	while (true) {
		// wraps the heading around if it goes above 360 or below 0
		if (chassis.getPose().theta < 0) chassis.setPose(chassis.getPose().x, chassis.getPose().y, (chassis.getPose().theta + 360));
		else if (chassis.getPose().theta > 360) chassis.setPose(chassis.getPose().x, chassis.getPose().y, (chassis.getPose().theta - 360));
		// delay to save resources
		delay(20);
	}
}
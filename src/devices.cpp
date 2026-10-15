#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "devices.hpp"

using namespace pros;

class Cascade {
	public:
		Cascade(pros::MotorGroup* motorGroup);
        pros::MotorGroup* motorGroup;
		enum Height{
			BASE = 0,
			ONE = 1, // temporary
			TWO = 2, // temporary
			THREE = 3, // temporary
			FOUR = 4, // temporary
			FIVE = 5, // temporary
			SIX = 6, // temporary
			SEVEN = 7, // temporary
			EIGHT = 8, // temporary
			NINE = 9, // temporary
			TEN = 10, // temporary
			ELEVEN = 11, // temporary
			TWELVE = 12, // temporary
			THIRTEEN = 13 // temporary
		};

		void score(Height height) {
			if (height != BASE) {
				motorGroup->move_absolute(height, 600);
			}
		}
		
		void reset() {
			motorGroup->move_absolute(BASE, 600);
		}
};


// Master controller
Controller master(E_CONTROLLER_MASTER);
// Left motor group
MotorGroup left_mg({-11, -12}, MotorGearset::blue);
// Right motor group
MotorGroup right_mg({19, 20}, MotorGearset::blue);
// Drivetrain settings
lemlib::Drivetrain drivetrainSettings(&left_mg,
							  &right_mg,
							  11.825, // temporary
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
// Pneumatic claw
adi::DigitalOut claw('A');
// Front distance sensor
Distance front_sensor(12);
// Cascade motor group
MotorGroup cascadeMotorGroup({10, -2}, MotorGearset::green);
// Cascade object for controlling the cascade lift
Cascade cascade(&cascadeMotorGroup);
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
lemlib::OdomSensors odomSensors(nullptr,
								nullptr,
								nullptr,
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
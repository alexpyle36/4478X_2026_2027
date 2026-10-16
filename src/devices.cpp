#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pid.hpp"
#include "drivercontrol.hpp"

using namespace pros;

/*struct Height {
	static constexpr double BASE = 0;
	static constexpr double ONE = 1; // temporary
	static constexpr double TWO = 2; // temporary
	static constexpr double THREE = 3; // temporary
	static constexpr double FOUR = 4; // temporary
	static constexpr double FIVE = 5; // temporary
	static constexpr double SIX = 6; // temporary
	static constexpr double SEVEN = 7; // temporary
	static constexpr double EIGHT = 8; // temporary
	static constexpr double NINE = 9; // temporary
	static constexpr double TEN = 10; // temporary
	static constexpr double ELEVEN = 11; // temporary
	static constexpr double TWELVE = 12; // temporary
	static constexpr double THIRTEEN = 13; // temporary
};*/

class Cascade {
	public:
		Cascade(MotorGroup* motorGroup) : motorGroup(motorGroup) {}
        MotorGroup* motorGroup;

		void score(double height) {
			if (height != 0) {
				motorGroup->move_absolute(height, 600);
			}
		}
		
		void reset() {
			motorGroup->move_absolute(0, 600);
		}
};


// Master controller
Controller master(E_CONTROLLER_MASTER);
// Left motor group
MotorGroup left_mg({-19, -20}, MotorGearset::blue);
// Right motor group
MotorGroup right_mg({11, 12}, MotorGearset::blue);
// Drivetrain settings
lemlib::Drivetrain drivetrainSettings(&left_mg,
							  &right_mg,
							  11.825, // temporary
							  lemlib::Omniwheel::NEW_325,
							  450,
							  2 // temporary
);
// Imu
Imu imu(13);
// Vertical tracking wheel encoder
/*Rotation vertical_sensor(8);*/
// Horizontal tracking wheel encoder
/*Rotation horizontal_sensor(9);*/
// Pneumatic claw
adi::DigitalOut claw('A', LOW);
// Front distance sensor
Distance front_sensor(12);
// Cascade motor group
MotorGroup cascadeMotorGroup({10, -2}, MotorGearset::green);
// Cascade object for controlling the cascade lift
//Cascade cascade(&cascadeMotorGroup);
// Vertical tracking wheel
/*lemlib::TrackingWheel vertical_tracking_wheel(&vertical_sensor,
											  lemlib::Omniwheel::NEW_2,
											  1 // temporary
);*/
// Horizontal tracking wheel
/*lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor,
											    lemlib::Omniwheel::NEW_2,
											    1 // temporary
);*/
// Odometry settings
lemlib::OdomSensors odomSensors(nullptr,
								nullptr,
								nullptr,
								nullptr,
								&imu
);
// Lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // Best working value: 10
											  0,
											  3, // Best working value: 3
											  3,
											  1,
											  100,
											  3,
											  500,
											  20 
);
// Angular PID controller
lemlib::ControllerSettings angular_controller(3, // Best working value: 3
											  0, // Best working value: 0
											  10, // Best working value: 10
											  0,
											  0,
											  0,
											  0,
											  0,
											  0 // Best working value: 0
);
// Input curve for throttle input during driver control
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
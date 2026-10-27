#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/motors.h"
#include <math.h>
#include "devices.hpp"

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

// Cascade class
Cascade::Cascade(AbstractMotor& motorgroup) : motors(motorgroup) {}

double Cascade::perimeter = ((0.164 * M_PI) + (((31.0 / 36.0) - 0.164) * 4));

int Cascade::inchesToDegrees(double inches) {
	return std::round((inches * 360) / perimeter);
}

double Cascade::degreesToInches(double deg) {
	return (deg * perimeter) / 360;
}

void Cascade::score(double height, scoreParams params) {// One half pin/cup is 3.25 inches
	if (params.inHalfPins) {
		height *= 3.25;
		if (params.goalType == Goal::ALLIANCE) height += 3.25;
		else if (params.goalType == Goal::NEUTRAL) height += 5.8;
		else height += 8.7;
	}

	motors.move_absolute(inchesToDegrees(height), params.maxspeed);
}	

void Cascade::setZeroPos(double inches) {
	motors.set_zero_position_all(inchesToDegrees(inches));
}

void Cascade::move(moveParams params) {
	if (params.up) motors.move_velocity(abs(params.maxspeed));
	else motors.move_velocity(-abs(params.maxspeed));
}

void Cascade::brake(/*brakeParams params*/) {
	motors.set_brake_mode_all(E_MOTOR_BRAKE_HOLD);
	motors.brake();
	/*if (params.snapToPin) {
		double height = Cascade::getHeight();
		double div = 3.25;
		double sub;
		if (params.goalType == Goal::ALLIANCE) {
			sub = 3.25;
		}
		else if (params.goalType == Goal::NEUTRAL) {
			sub = 5.8;
		}
		else {
			sub = 8.7;
		}
		height -= sub;
		height /= div;
		int i = 0;
		while ((i * div + sub) < height) {
			i++;
		}
		if (((i * div + sub) - height) < (height - ((i - 1) * div))) {
			Cascade::score((i * div + sub), {.inHalfPins = true});
		} else {
			Cascade::score(std::max(0.0, (i - 1) * div), {.inHalfPins = true});
		}
	}*/
}

double Cascade::getHeight() {
	double totalPos = 0;
	for (int i = 0; i < motors.size(); i++) {
		totalPos += motors.get_position(i);
	}
	return degreesToInches(totalPos / motors.get_position_all().size());;
}

/*--------------------------------------------------------------------------------------*/

Claw::Claw(adi::DigitalOut& pnuematic) : piston(pnuematic) {}

void Claw::setClaw(clawState state) {
	currentClawState = state;
	piston.set_value(state);
}

Claw::clawState Claw::getState() {
	return currentClawState;
}

// Master controller
Controller master(E_CONTROLLER_MASTER);
// Left motor group
MotorGroup left_mg({-11, -12}, MotorGearset::blue);
// Right motor group
MotorGroup right_mg({19, 20}, MotorGearset::blue);
// Drivetrain settings
lemlib::Drivetrain drivetrainSettings(&left_mg,
							  &right_mg,
							  11.5, // temporary 
							  lemlib::Omniwheel::NEW_325,
							  450,
							  2 // temporary
);
// Imu
Imu imu(15);
// Vertical tracking wheel encoder
Rotation vertical_sensor(8);
// Horizontal tracking wheel encoder
Rotation horizontal_sensor(9);
// Pneumatic claw
adi::DigitalOut clawADI('A');
// Claw object for controlling the claw pneumatic
Claw claw(clawADI);
// Front distance sensor
Distance front_sensor(13);
// Right distance sensor
Distance right_sensor(14);
// Back distance sensor
Distance back_sensor(16);
// Left distance sensor
Distance left_sensor(17);
// Cascade motor group
MotorGroup cascadeMotorGroup({1, -2, 9, -10}, MotorGearset::green);
// Cascade object for controlling the cascade lift
Cascade cascade(cascadeMotorGroup);
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
lemlib::ControllerSettings angular_controller(2.35, // Best working value: 2.35
											  0.001, // Best working value: 0
											  19.0, // Best working value: 19
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
#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
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

//A PID that detects when the robot's angle changes by too much and stops the motion, then corrects it.
void impactCorrectionPID(double inches) {
	lemlib::PID pid(2, 0, 10);
	double startL = (left_mg.get_position(0) + left_mg.get_position(1) + left_mg.get_position(2) / 3);
	double startR = (right_mg.get_position(0) + right_mg.get_position(1) + right_mg.get_position(2) / 3);
	double errorL = inches;
	double errorR = inches;
	while (errorL > 0.5 && errorR > 0.5) {
		double currentPosL = (left_mg.get_position(0) + left_mg.get_position(1) + left_mg.get_position(2) / 3);
		double currentPosR = (right_mg.get_position(0) + right_mg.get_position(1) + right_mg.get_position(2) / 3);
		double theta = chassis.getPose().theta;
		errorL = (startL + inches) - currentPosL;
		errorR = (startR + inches) - currentPosR;
		left_mg.move_velocity(pid.update(errorL));
		right_mg.move_velocity(pid.update(errorR));
		if (chassis.getPose().theta > theta + 3) {
			left_mg.brake();
			right_mg.brake();
			chassis.cancelMotion();
			chassis.swingToHeading(theta, DriveSide::LEFT, 1000, {.maxSpeed = 50});
			errorL = 0;
			errorR = 0;
		} else if (chassis.getPose().theta < theta - 3) {
			left_mg.brake();
			right_mg.brake();
			chassis.cancelMotion();
			chassis.swingToHeading(theta, DriveSide::LEFT, 1000, {.maxSpeed = 50});
			errorL = 0;
			errorR = 0;
		}
	}
	left_mg.brake();
	right_mg.brake();
}

void cascadePID(double inches){
	lemlib::PID liftpid(2, 0 , 10);

}

void PID_tuning(PID type) {
	chassis.setPose(0, 0, 0);
	switch (type) {
		case LATERAL:
    		chassis.moveToPoint(0, 24, 100000);
			break;
		case ANGULAR:
    		chassis.turnToHeading(90, 100000);
			break;
		case CORECTER:
			drivePID(24);
			break;
		case CASCADE:
			cascadePID(5);
	}
}
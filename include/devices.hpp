#pragma once

#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/abstract_motor.hpp"

class Cascade{
    public:
        Cascade(pros::AbstractMotor& motorgroup);

        void score(double height, int maxspeed = 200);
        
        void reset();

        void raise(int maxspeed = 200);

        void lower(int maxspeed = 200);
    private:
        pros::MotorGroup motors;
};

extern pros::Controller master;
extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;
extern lemlib::Drivetrain drivetrainSettings;
extern pros::Imu imu;
extern pros::Rotation vertical_sensor;
extern pros::Rotation horizontal_sensor;
extern pros::MotorGroup cascadeMotorGroup;
extern Cascade cascade;
extern pros::adi::DigitalOut claw;
extern pros::Distance front_sensor;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::OdomSensors odomSensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;
extern lemlib::Chassis chassis;
#pragma once

#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep

enum class Goal {
    ALLIANCE,
    NEUTRAL,
    CENTER
};

struct scoreParams {
    int maxspeed = 200;
    bool inHalfPins = false;
    Goal goalType = Goal::ALLIANCE;
};

struct moveParams {
    int maxspeed = -1; // Use the cascade's maximum speed.
    bool up = true;
};

/*struct brakeParams {
    bool snapToPin = false;
    Goal goalType = Goal::ALLIANCE;
};*/

class Cascade {
    public:
        Cascade(pros::AbstractMotor& motorgroup);

        void score(double height, scoreParams params = {});
        
        void setZeroPos(double inches = -4.5);

        void move(moveParams params = {});

        void brake(/*brakeParams params = {}*/);

        double getHeight();

        int maxMotorSpeed();
    private:
        pros::MotorGroup motors;

        static int inchesToDegrees(double inches);

        static double degreesToInches(double deg);

        static double perimeter;
};



class Claw{
    public:
        Claw(pros::adi::DigitalOut& pnuematic);

        enum clawState {
            CLOSED = false,
            OPEN = true
        };

        void setClaw(clawState state);

        clawState getState();
    private:
        pros::adi::DigitalOut piston;
        clawState currentClawState = CLOSED;
};

extern pros::Controller master;
extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;
extern pros::MotorGroup cascadeMotorGroup;
extern Cascade cascade;
extern Claw claw;
extern pros::Distance front_sensor;
extern pros::Distance right_sensor;
extern pros::Distance back_sensor;
extern pros::Distance left_sensor;
extern lemlib::Chassis chassis;
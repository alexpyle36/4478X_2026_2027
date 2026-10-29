#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "distance.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"
#include "devices.hpp"

using namespace pros;

void rayCastingInitialize() {
        // Variables

    lemlib::Pose distPose(chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta); 

    const double C = 3568.7;

    const double fHorOffset = 1; // temp
    const double rHorOffset = 2; // temp
    const double bHorOffset = 3; // temp
    const double lHorOffset = 4; // temp
    const double fVertOffset = 1; // temp
    const double rVertOffset = 2; // temp
    const double bVertOffset = 3; // temp
    const double lVertOffset = 4; // temp

    int frontWall;
    int rightSideOfWall;

    double fDist = front_sensor.get_distance();
    double rDist = right_sensor.get_distance();
    double bDist = back_sensor.get_distance();
    double lDist = left_sensor.get_distance();

    double A;
    double B;

    double alpha;
    double R;
    double distTheta;
    double distX;
    double distY;

    // Control structs

    if (chassis.getPose().theta >= 225 && chassis.getPose().theta < 315) frontWall = 4;
    else if (chassis.getPose().theta >= 135 && chassis.getPose().theta < 225) frontWall = 3;
    else if (chassis.getPose().theta >= 45 && chassis.getPose().theta < 135) frontWall = 2;
    else frontWall = 1;

    switch (frontWall) {
        case 1:
            A = fDist + bDist + fVertOffset + bVertOffset;
            B = fHorOffset + bHorOffset;
            if (chassis.getPose().theta < 45) rightSideOfWall = 1;
            else rightSideOfWall = -1;
            break;
        case 2:
            A = rDist + lDist + rVertOffset + lVertOffset;
            B = rHorOffset + lHorOffset;
            if (chassis.getPose().theta < 90) rightSideOfWall = -1;
            else rightSideOfWall = 1;
            break;
        case 3:
            A = bDist + fDist + bVertOffset + fVertOffset;
            B = bHorOffset + fHorOffset;
            if (chassis.getPose().theta < 180) rightSideOfWall = -1;
            else rightSideOfWall = 1;
            break;
        case 4:
            A = lDist + rDist + lVertOffset + rVertOffset;
            B = lHorOffset + rHorOffset;
            if (chassis.getPose().theta < 270) rightSideOfWall = -1;
            else rightSideOfWall = 1;
            break;
    }

    // Math

    alpha = std::atan2(B, A);
    R = std::sqrt(std::pow(A, 2) + std::pow(B, 2));
    distTheta = alpha + (rightSideOfWall * std::acos(C / R));
    switch (frontWall) {
        case 1:
            distX = (((C / 2) - (rDist + rVertOffset) * std::cos(distTheta)) + ((C / -2) + (lDist + lVertOffset) * std::cos(distTheta))) / 2;
            distY = (((C / 2) - (fDist + fVertOffset) * std::cos(distTheta)) + ((C / -2) + (bDist + bVertOffset) * std::cos(distTheta))) / 2;
            break;
        case 2:
            distX = (((C / 2) - (fDist + fVertOffset) * std::cos(distTheta)) + ((C / -2) + (bDist + bVertOffset) * std::cos(distTheta))) / 2;
            distY = (((C / 2) - (lDist + rVertOffset) * std::cos(distTheta)) + ((C / -2) + (rDist + rVertOffset) * std::cos(distTheta))) / 2;
            break;
        case 3:
            distX = (((C / 2) - (lDist + rVertOffset) * std::cos(distTheta)) + ((C / -2) + (rDist + rVertOffset) * std::cos(distTheta))) / 2;
            distY = (((C / 2) - (bDist + bVertOffset) * std::cos(distTheta)) + ((C / -2) + (fDist + fVertOffset) * std::cos(distTheta))) / 2;
            break;
        case 4:
            distX = (((C / 2) - (bDist + bVertOffset) * std::cos(distTheta)) + ((C / -2) + (fDist + fVertOffset) * std::cos(distTheta))) / 2;
            distY = (((C / 2) - (rDist + rVertOffset) * std::cos(distTheta)) + ((C / -2) + (lDist + lVertOffset) * std::cos(distTheta))) / 2;
            break;
    }

    distTheta = 180 * distTheta / M_PI;

    // Setting starting pose

    distPose = lemlib::Pose(distX, distY, distTheta);
    chassis.setPose(distPose);
}

void mainDisp_fn() {
    int overheated = 0;
    float theta;
    while (true) {
        theta = chassis.getPose().theta;
        theta = wrap(theta, 0, 360);
        lcd::print(1, "Theta: %.2f", theta);
        lcd::print(4, "e: %.2f", cascadeMotorGroup.get_target_position(0));
        lcd::print(5, "e: %.2f", cascadeMotorGroup.get_target_position(1));
        lcd::print(6, "e: %.2f", cascadeMotorGroup.get_target_position(2));
        lcd::print(7, "e: %.2f", cascadeMotorGroup.get_target_position(3));
        if ((cascadeMotorGroup.is_over_temp(0) == 1) || (cascadeMotorGroup.is_over_temp(1) == 1)) {
            overheated += 1;
        }
        if (left_mg.is_over_temp(0) == 1 || left_mg.is_over_temp(1) == 1 || right_mg.is_over_temp(0) == 1 || right_mg.is_over_temp(1) == 1) {
            overheated += 2;
        }
        switch (overheated) {
            case 0:
                master.print(2, 0, "Heated: None");
                break;
            case 1:
                master.print(2, 0, "Heated: Cascade");
                break;
            case 2:
                master.print(2, 0, "Heated: Drive");
                break;
            case 3:
                master.print(2, 0, "Heated: All");
                break;
        }
        delay(100);
    }
}

double expectedHeading = 0;
double expectedDistance = 0;

void pidErrorDisp_fn() {
    while (true) {
        if (expectedHeading != 0) master.print(2, 0, "Theta Error: %.2f", chassis.getPose().theta - expectedHeading);
        if (expectedDistance != 0) master.print(2, 0, "Dist: %.2f", chassis.getPose().y); lcd::print(3, "Dist: %.2f", chassis.getPose().y);
        delay(20);
    }
}

Task mainDisp(mainDisp_fn);
Task pidErrorDisp_task(pidErrorDisp_fn);

bool on = true;

void pidErrorDisp(double expectedTheta, double expectedDist) {
    expectedHeading = expectedTheta;
    expectedDistance = expectedDist;
    if (!on) {
        pidErrorDisp_task.resume();
        on = !on;
    } else {
        pidErrorDisp_task.suspend();
        on = !on;
    }
}

void pidErrorDisp() {
    if (!on) {
        pidErrorDisp_task.resume();
        on = !on;
    } else {
        pidErrorDisp_task.suspend();
        on = !on;
    }
}

void initialize_fn() {
    lcd::initialize();
    buttons.suspend();
    pidErrorDisp();
    chassis.calibrate(); // calibrate sensors
    mainDisp.suspend();
    claw.setClaw(Claw::CLOSED);
    //rayCastingInitialize();
}
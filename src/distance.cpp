#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "distance.hpp"
#include "devices.hpp" 

using namespace pros;

bool objectDetected = false;
Dist dir;

void findObject_fn() {
	while (true) {
		if (dir == Dist::FRONT) {
			if (front_sensor.get_object_size() > 100 && front_sensor.get_object_size() < 200) {
				chassis.cancelMotion();
				objectDetected = true;
				break;
			}
			else {
				objectDetected = false;
			}
		}
		if (dir == Dist::RIGHT) {
			if (right_sensor.get_object_size() > 100 && right_sensor.get_object_size() < 200) {
				chassis.cancelMotion();
				objectDetected = true;
				break;
			}
			else {
				objectDetected = false;
			}
		}
		if (dir == Dist::BACK) {
			if (back_sensor.get_object_size() > 100 && back_sensor.get_object_size() < 200) {
				chassis.cancelMotion();
				objectDetected = true;
				break;
			}
			else {
				objectDetected = false;
			}
		}
		if (dir == Dist::LEFT) {
			if (left_sensor.get_object_size() > 100 && left_sensor.get_object_size() < 200) {
				chassis.cancelMotion();
				objectDetected = true;
				break;
			}
			else {
				objectDetected = false;
			}
		}
		delay(20);
	}
}

Task findObject(findObject_fn);

void turnToFind(float aproxTheta, Dist side) {
	dir = side;
	findObject.resume();
	chassis.turnToHeading(aproxTheta - 15, 2000);
	chassis.turnToHeading(aproxTheta, 2000);
	chassis.turnToHeading(aproxTheta + 15, 2000);
	chassis.turnToHeading(aproxTheta, 2000);
	findObject.suspend();
	objectDetected = false;
}

lemlib::Pose rayCasting() {
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

    const double maxLinearError = 5;
    const double maxThetaError = 5;

    double xError;
    double yError;
    double linearError;
    double thetaError;

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

    // Sanity check

    xError = distX - chassis.getPose().x;
    yError = distY - chassis.getPose().y;
    linearError = std::sqrt(std::pow(xError, 2) + std::pow(yError, 2));
    thetaError = lemlib::angleError(chassis.getPose().theta, distTheta);
    if (linearError < maxLinearError && thetaError < maxThetaError) distPose = lemlib::Pose(distX, distY, distTheta);
    
    // Return

    return distPose;
}
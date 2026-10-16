#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonroutes.hpp"
#include "distance.hpp"
#include "pneumatics.hpp"
#include "pid.hpp"
#include "drivercontrol.hpp"
#include "functions.hpp"
#include "devices.hpp"

using namespace pros;

void buttons_fn() {
	// State for button effects (0 = off, 1 = on)
	int L1State = 0;
	int L2State = 0;
	int R1State = 0;
	
	while (true) {
		bool buttonL1 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1); // Bool for controller button "L1"
		bool buttonL2 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2); // Bool for controller button "L2"
		bool buttonR1 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1); // Bool for controller button "R1"
		
		if (buttonL1) L1State = (L1State == 1) ? 0 : 1; // State switch for button "L1" effect
		if (buttonL2) L2State = (L2State == 1) ? 0 : 1; // State switch for button "L2" effect
		if (buttonR1) R1State = (R1State == 1) ? 0 : 1; // State switch for button "R1" effect
		
		if (L1State == 1) { // State effect for button "L1"
            
        } else if (L1State == 0) {
            
        }
		if (L2State == 1) { // State effect for button "L2"
			
		} else if (L2State == 0) {
			
		}
		if (R1State == 1) { // State effect for button "R1"
			setClaw(OPEN);
		} else if (R1State == 0) {
			setClaw(CLOSED);
		}

		// 20 msec delay to save resources
		delay(20);
	}
}

// Task for handling the controller butons
Task buttons(buttons_fn);

void joysticks() {
	// Left y axis controler position
	int leftY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
	// Right y axis controler position
	int rightY = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		
	// Move the robot based of of inputs from the controlers left and right y axis position
	chassis.tank(leftY, rightY);
}
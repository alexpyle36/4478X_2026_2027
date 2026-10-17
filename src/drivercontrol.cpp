#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "drivercontrol.hpp"
#include "devices.hpp"

using namespace pros;

void buttons_fn() {
	// State for button effects (-1 = reverse, 0 = off, 1 = on)
	bool clawState = 0;
	
	while (true) {
		bool buttonL2 = master.get_digital(E_CONTROLLER_DIGITAL_L2); // Bool for controller button "L1"
		bool buttonR2 = master.get_digital(E_CONTROLLER_DIGITAL_R2); // Bool for controller button "L2"
		bool buttonB = master.get_digital_new_press(E_CONTROLLER_DIGITAL_B); // Bool for controller button "R1"
		
		if (buttonB) clawState = !clawState; claw.set_value(clawState); 

		// selection process for the cascade buttons
		if (buttonL2 && !buttonR2) cascade.raise();
		else if (buttonR2 && !buttonL2) cascade.lower();
		else cascadeMotorGroup.brake();

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
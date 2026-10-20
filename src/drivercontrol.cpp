#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "drivercontrol.hpp"
#include "devices.hpp"
#include "pros/misc.h"

using namespace pros;

void buttons_fn() {
	// State for button effects (1 = Alliance, 2 = Neutral, 3 = Center)
	// Goal GoalType = Goal::ALLIANCE;
	
	while (true) {
		bool buttonL1 = master.get_digital(E_CONTROLLER_DIGITAL_L1); // Bool for controller button "L1"
		bool buttonR1 = master.get_digital(E_CONTROLLER_DIGITAL_R1); // Bool for controller button "L2"
		bool buttonB = master.get_digital_new_press(E_CONTROLLER_DIGITAL_B); // Bool for controller button "B"
		// bool buttonA = master.get_digital_new_press(E_CONTROLLER_DIGITAL_A); // Bool for controller button "A"

		if (buttonB) claw.setClaw(claw.getState() == Claw::CLOSED ? Claw::OPEN : Claw::CLOSED);

		/*if (buttonA) {
			switch (GoalType) {
				case Goal::ALLIANCE:
					GoalType = Goal::NEUTRAL;
					break;
				case Goal::NEUTRAL:
					GoalType = Goal::CENTER;
					break;
				case Goal::CENTER:
					GoalType = Goal::ALLIANCE;
					break;
			}
		}*/
		
		// selection process for the cascade buttons
		if (buttonR1 && !buttonL1) cascade.move();
		else if ((cascade.getHeight() <= 36)) cascade.brake();
		else if (buttonL1 && !buttonR1) cascade.move({.up = false});
		else cascade.brake(/*{.snapToPin = true, .goalType = GoalType}*/);
	
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
#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pneumatics.hpp"
#include "pros/misc.hpp"
#include <cmath>
#include "drivercontrol.hpp"

using namespace pros;

// Master controller
Controller master(E_CONTROLLER_MASTER);
// First pneumatic
adi::DigitalOut pneumatic1('A');
// Second pneumatic
adi::DigitalOut pneumatic2('B');

void buttons_fn() {
	// State for button "L1" effects (0 = off, 1 = on)
	int L1State = 0;
	int L2State = 0;
	int R1State = 0;
	int R2State = 0;
	int UpState = 0;
	int RightState = 0;
	int DownState = 0;
	int LeftState = 0;
	int XState = 0;
	int AState = 0;
	int BState = 0;
	int YState = 0;
	while (true) {

		bool buttonL1 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1); // Bool for controller button "L1"
		bool buttonL2 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2); // Bool for controller button "L2"
		bool buttonR1 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1); // Bool for controller button "R1"
		bool buttonR2 = master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2); // Bool for controller button "R2"
		bool buttonUp = master.get_digital_new_press(E_CONTROLLER_DIGITAL_UP); // Bool for controller button "Up"
		bool buttonRight = master.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT); // Bool for controller button "Right"
		bool buttonDown = master.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN); // Bool for controller button "Down"
		bool buttonLeft = master.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT); // Bool for controller button "Left"
		bool buttonX = master.get_digital_new_press(E_CONTROLLER_DIGITAL_X); // Bool for controller button "X"
		bool buttonA = master.get_digital_new_press(E_CONTROLLER_DIGITAL_A); // Bool for controller button "A"
		bool buttonB = master.get_digital_new_press(E_CONTROLLER_DIGITAL_B); // Bool for controller button "B"
		bool buttonY = master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y); // Bool for controller button "Y"

		
		if (buttonL1) { // State switch for button "L1" effect
			L1State = (L1State == 1) ? 0 : 1;
		}
		if (buttonL2) { // State switch for button "L2" effect
			L2State = (L2State == 1) ? 0 : 1;
		}
		if (buttonR1) { // State switch for button "R1" effect
			R1State = (R1State == 1) ? 0 : 1;
		}
		if (buttonR2) { // State switch for button "R2" effect
			R2State = (R2State == 1) ? 0 : 1;
		}
		if (buttonUp) { // State switch for button "Up" effect
			UpState = (UpState == 1) ? 0 : 1;
		}
		if (buttonRight) { // State switch for button "Right" effect
			RightState = (RightState == 1) ? 0 : 1;
		}
		if (buttonDown) { // State switch for button "Down" effect
			DownState = (DownState == 1) ? 0 : 1;
		}
		if (buttonLeft) { // State switch for button "Left" effect
			LeftState = (LeftState == 1) ? 0 : 1;
		}
		if (buttonX) { // State switch for button "X" effect
			XState = (XState == 1) ? 0 : 1;
		}
		if (buttonA) { // State switch for button "A" effect
			AState = (AState == 1) ? 0 : 1;
		}
		if (buttonB) { // State switch for button "B" effect
			BState = (BState == 1) ? 0 : 1;
		}
		if (buttonY) { // State switch for button "Y" effect
			YState = (YState == 1) ? 0 : 1;
		}

		
		if (L1State == 1) { // State effect for button "L1"
            
        } else if (L1State == 0) {
            
        }
		if (L2State == 1) { // State effect for button "L2"
            
        } else if (L2State == 0) {
            
        }
		if (R1State == 1) { // State effect for button "R1"
            
        } else if (R1State == 0) {
            
        }
		if (R2State == 1) { // State effect for button "R2"
            
        } else if (R2State == 0) {
            
        }
		if (UpState == 1) { // State effect for button "Up"
            
        } else if (UpState == 0) {
            
        }
		if (RightState == 1) { // State effect for button "Right"
            
        } else if (RightState == 0) {
            
        }
		if (DownState == 1) { // State effect for button "Down"
            
        } else if (DownState == 0) {
            
        }
		if (LeftState == 1) { // State effect for button "Left"
            
        } else if (LeftState == 0) {
            
        }
		if (XState == 1) { // State effect for button "X"
            
        } else if (XState == 0) {
            
        }
		if (AState == 1) { // State effect for button "A"
            
        } else if (AState == 0) {
            
        }
		if (BState == 1) { // State effect for button "B"
            
        } else if (BState == 0) {
            
        }
		if (YState == 1) { // State effect for button "Y"
            
        } else if (YState == 0) {
            
        }

		// 20 msec delay to save resources
		delay(20);
	}
}
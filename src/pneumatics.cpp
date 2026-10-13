#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pneumatics.hpp"

using namespace pros;

// First pneumatic
adi::DigitalOut pneumatic1('A');
// Second pneumatic
adi::DigitalOut pneumatic2('B');
// Third pneumatic
adi::DigitalOut pneumatic3('C');

void setPneumatic1(PneumaticState toggle) {
    switch (toggle) {
		case OUT:
            pneumatic1.set_value(false);
			break;
        case IN:
            pneumatic1.set_value(false);
			break;
	}
}

void setPneumatic2(PneumaticState toggle) {
	switch (toggle) {
		case OUT:
            pneumatic2.set_value(false);
			break;
        case IN:
            pneumatic2.set_value(false);
			break;
	}
}
#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pneumatics.hpp"
#include "devices.hpp"

using namespace pros;

void setClaw(PneumaticState toggle) {
    switch (toggle) {
		case CLOSED:
            claw.set_value(false);
			break;
        case OPEN:
            claw.set_value(true);
			break;
	}
}
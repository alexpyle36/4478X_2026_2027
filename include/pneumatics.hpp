#pragma once

enum PneumaticState {
    CLOSED,
    OPEN
};

void setClaw(PneumaticState toggle);
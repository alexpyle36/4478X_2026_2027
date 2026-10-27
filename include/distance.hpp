#pragma once

#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep

enum Dist {
    FRONT,
    RIGHT,
    BACK,
    LEFT
};

void turnToFind(float aproxTheta);

lemlib::Pose rayCasting();
#pragma once

#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep


extern pros::Task mainDisp;
extern pros::Task pidErrorDisp_task;

void headingErrorDisp(double expectedTheta, double expectedDist);
void initialize_fn();
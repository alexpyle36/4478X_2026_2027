#pragma once

#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep


extern pros::Task mainDisp;
extern pros::Task pidErrorDisp_task;

void pidErrorDisp(double expectedTheta, double expectedDist);
void pidErrorDisp();
void initialize_fn();
#pragma once

#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep

void initialize_fn();

extern pros::Task headingDisp;
extern pros::Task overheatedDisp;
extern pros::Task headingErrorDisp_task;
extern pros::Task distanceErrorDisp_task;

void headingErrorDisp(double expected);
void distanceErrorDisp(double expected);
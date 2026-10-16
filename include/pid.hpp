#pragma once

#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep

enum PID {
	LATERAL,
	ANGULAR,
	ALL
};

void PID_tuning(PID type);


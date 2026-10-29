#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "devices.hpp" // IWYU pragma: keep
#include "functions.hpp"

using namespace pros;

// wraps a value around a min and max value.
// min is exclusive, max is inclusive.
double wrap(double value, double min, double max) {
	if (value < min) value += max;
	else if (value >= max) value -= std::abs(max - min);
	return value;
}
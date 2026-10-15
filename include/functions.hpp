#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep

using namespace pros;

void headingWrap_fn();
void poseReset_fn();
void impactCorrection_fn();

extern pros::Task headingWrap;
extern pros::Task poseReset;
extern pros::Task impactCorrection;
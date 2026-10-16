#pragma once

enum autonroute {
    Skills = 1,
    Base = 2,
    Left = 3,
    Right = 4,
    AWP = 5,
};

void baseAuton();

void skillsAuton();

void leftAuton();

void rightAuton();

void AWPAuton();

void autonRoute(autonroute route);
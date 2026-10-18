#pragma once

enum autonroute {
    Skills = 1,
    FullSkills = 2,
    Base = 3,
    Left = 4,
    Right = 5,
    AWP = 6
};

void baseAuton();

void skillsAuton();

void leftAuton();

void rightAuton();

void AWPAuton();

void autonRoute(autonroute route);
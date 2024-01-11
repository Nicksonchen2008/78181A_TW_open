#pragma once

#include "pros/adi.hpp"
#include "pros/rotation.hpp"
#include "pros/motors.hpp"
#include "pros/misc.hpp"

extern pros::ADIDigitalOut wings;
extern pros::ADIDigitalOut wings1;
extern pros::ADIDigitalOut pistonIntake;
extern pros::ADIDigitalOut blocker;

extern pros::ADIDigitalIn upSelect;

extern pros::Motor intakeMotor;

extern pros::Motor cataMotor;
extern pros::Motor cataMotor1;
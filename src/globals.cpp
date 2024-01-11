#include "globals.hpp"
#include "main.h"

pros::MotorGroup leftMotors(std::initializer_list<pros::Motor> {
    pros::Motor(-8, pros::E_MOTOR_GEAR_BLUE),
    pros::Motor(-2, pros::E_MOTOR_GEAR_BLUE),
    pros::Motor(3, pros::E_MOTOR_GEAR_BLUE),
});

pros::MotorGroup rightMotors(std::initializer_list<pros::Motor> {
    pros::Motor(4, pros::E_MOTOR_GEAR_BLUE),
    pros::Motor(5, pros::E_MOTOR_GEAR_BLUE),
    pros::Motor(-6, pros::E_MOTOR_GEAR_BLUE),
});

pros::Imu imu(1);

pros::ADIDigitalOut wings('H');
pros::ADIDigitalOut wings1('A');

pros::ADIDigitalOut pistonIntake('B');
pros::ADIDigitalOut blocker('G');

pros::ADIDigitalIn upSelect('e');
    
pros::Motor intakeMotor(-7);

pros::Motor cataMotor(9);
pros::Motor cataMotor1(10);


#include "opcontrol.hpp"
#include "main.cpp"
#include "globals.hpp"

bool pistonIntakeValue = false;
bool blockerValue = false;
bool matchloadValue = false;

void driver(){
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    leftMotors.move_voltage((leftY+rightX)*120);
    rightMotors.move_voltage((leftY-rightX)*120);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        blockerValue = !blockerValue; 
        blocker.set_value(blockerValue);
    }

    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
        chassis.setPose(35,50,180);
        chassis.moveToPose(62, 42, 77, 2000);

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        pistonIntakeValue = !pistonIntakeValue; 
        pistonIntake.set_value(pistonIntakeValue);
    }
        
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intakeMotor.move(127);
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeMotor.move(-127);
    } else {
        intakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
        intakeMotor.brake();
    }

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
        cataMotor.move_velocity(110);
        cataMotor1.move_velocity(110);
    }
    else{
        cataMotor.set_brake_mode(MOTOR_BRAKE_COAST);
        cataMotor1.set_brake_mode(MOTOR_BRAKE_COAST);
        cataMotor.brake();
        cataMotor1.brake();
    }

    if(controller.get_digital(DIGITAL_L2)){
        wings.set_value(true);
        wings1.set_value(true);
    }
    else{
        wings.set_value(false);
        wings1.set_value(false);
    }
}
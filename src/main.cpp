#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/logger/stdout.hpp"
#include "autoSelect/selection.h"
#include "pros/misc.h"
#include "autons.hpp"
#include "globals.hpp"
#include "globals.cpp"
#include "opcontrol.hpp"
#include "opcontrol.cpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::Rotation horizontalEnc(21);

lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_325, -4.7);

lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              13, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 3.25" omnis
                              343, // drivetrain rpm is 360
                              15 // chase power is 2. If we had traction wheels, it would have been 8
);

lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            3, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angularController(1.49, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to nullptr as we don't have one
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have one
                            &horizontal, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
    switch(selector::auton){
        case 0: 
            skills(); 
            break;
        case 1: 
            sixball(); 
            break;
        case 2: 
            AWPannoy(); 
            break;
        case 3: 
            balls(); 
            break;
        case 4: 
            AWPsafe(); 
            break;
        default: 
            skills();
            break;
    } 
}

void opcontrol() {
    while (true) {
        driver();
    }
    pros::delay(10);
}

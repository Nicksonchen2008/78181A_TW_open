#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/logger/stdout.hpp"
#include "autoSelect/selection.h"
#include "pros/misc.h"
#include "autons.hpp"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
// pros::Motor lF(-8, pros::E_MOTOR_GEARSET_06); // left front motor. port 8, reversed
// pros::Motor lM(-20, pros::E_MOTOR_GEARSET_06); // left middle motor. port 20, reversed
// pros::Motor lB(19, pros::E_MOTOR_GEARSET_06); // left back motor. port 19
// pros::Motor rF(2, pros::E_MOTOR_GEARSET_06); // right front motor. port 2
// pros::Motor rM(11, pros::E_MOTOR_GEARSET_06); // right middle motor. port 11
// pros::Motor rB(-13, pros::E_MOTOR_GEARSET_06); // right back motor. port 13, reversed

// // motor groups
// pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
// pros::MotorGroup rightMotors({rF, rM, rB}); // right motor group
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

// Inertial Sensor on port 11
pros::Imu imu(1);


pros::ADIDigitalOut wings('H');
pros::ADIDigitalOut wings1('A');

pros::ADIDigitalOut pistonIntake('B');
pros::ADIDigitalOut blocker('G');

pros::ADIDigitalIn upSelect('e');
    
pros::Motor intakeMotor(-7);
// pros::Motor intakeMotor2(21);

// pros::MotorGroup intakeMotor{intakeMotor1,intakeMotor2};


pros::Motor cataMotor(9);
pros::Motor cataMotor1(10);
// pros::Motor cataMotor1(1);
// tracking wheels
pros::Rotation horizontalEnc(21);
// horizontal tracking wheel. 2.75" diameter, 3.7" offset, back of the robot
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_325, -4.7);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              13, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 3.25" omnis
                              343, // drivetrain rpm is 360
                              15 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
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

// angular motion controller
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
// sensors for odometry
// note that in this example we use internal motor encoders, so we don't pass vertical tracking wheels
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to nullptr as we don't have one
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have one
                            &horizontal, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    selector::init();
    // chassis.setPose(36,-60, 45);
    
    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        // chassis.setPose(35,50,180);
        // lemlib::Pose (35,50,180);
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

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function

//AWP

//skills

//sixball
// ASSET(firsttwo_txt);
// ASSET(thirdball1_txt);
// ASSET(thirdball2_txt);
// ASSET(thirdtospit_txt);  
// ASSET(intakefourth_txt);
// ASSET(doohickey_txt);
// ASSET(prepareforram_txt);
// ASSET(finalram_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
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
    // AWPsafe();
    // balls();
    // threeBallTouch();
    // AWPannoy();
    // sixball();
    // skills();
    // swingtest();
    
    
    // chassis.moveTo(32, 59, 270, 4000, true, 2, 0.6, 127, false);
    // chassis.turnTo(300, 0 ,2000);

    // // example movement: Move to x: 20 and y:15, and face heading 90. Timeout set to 4000 ms
    // chassis.moveTo(20, 15, 90, 4000);
    // // example movement: Turn to face the point x:45, y:-45. Timeout set to 1000
    // // dont turn faster than 60 (out of a maximum of 127)
    // chassis.turnTo(45, -45, 1000, true, 60);
    // example movement: Follow the path in path.txt. Lookahead at 15, Timeout set to 4000
    // following the path with the back of the robot (forwards = false)
    // see line 116 to see how to define a path
    
    // wait until the chassis has travelled 10 inches. Otherwise the code directly after
    // the movement will run immediately
    // Unless its another movement, in which case it will wait
    // chassis.waitUntil(10);
    // pros::lcd::print(4, "Travelled 10 inches during pure pursuit!");
    // wait until the movement is done
    // chassis.waitUntilDone();
    // pros::lcd::print(4, "pure pursuit finished!");
}

/**
 * Runs in driver control
 */
void opcontrol() {
    bool pistonIntakeValue = false;
    bool blockerValue = false;
    bool matchloadValue = false;
    // controller
    // loop to continuously update motors
    while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // move the chassis with curvature drive
        leftMotors.move_voltage((leftY+rightX)*120);
        rightMotors.move_voltage((leftY-rightX)*120);
        // chassis.curvature(leftY, rightX);
        // delay to save resources
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            blockerValue = !blockerValue; 
            blocker.set_value(blockerValue);
        }

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
            chassis.setPose(35,50,180);
            chassis.moveToPose(62, 42, 77, 2000);
            // chassis.moveToPose(62, 42, 77, 2000, true, 6, 0.6, 127,50, 0 , false);
        }

            // if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            //     setCataMode(cataHalfway);
            // } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            //     setCataMode(cataBottom);
            
            // }

            // wings.set_value(false);
    
        // } else {
            
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            pistonIntakeValue = !pistonIntakeValue; 
            pistonIntake.set_value(pistonIntakeValue);
        }
            
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            intakeMotor.move(127);
                // intakeMotor2.move(127);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intakeMotor.move(-127);
                // intakeMotor2.move(-127);
        } else {
            intakeMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
            intakeMotor.brake();
                // intakeMotor2.move(0);
        }

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            cataMotor.move_velocity(110);
            cataMotor1.move_velocity(110);
            
            // cataMatchloadSpeed(99);
        }
        // else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            
        // }
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
    pros::delay(10);
}

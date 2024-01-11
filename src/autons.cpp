#include "autons.hpp"
#include "main.cpp"

void AWPsafe() {
}

void balls() {
}

void AWPannoy() {
}

void threeBallTouch() {
}

void fiveballrisky() {
}

void sixball() {
}

void skills() {
    chassis.setPose(35,50,0);
    chassis.moveToPose(60, 41, 257, 2000);
    // chassis.moveToPose(60, 41, 257, 2000, false, 5, 0.5, 127, false);

    cataMotor.move(110);
    cataMotor1.move(110);
}

void swingtest(){
    chassis.setPose(36,-36,270);
    // chassis.swingTo(90,true,1000,127,false);//true = right side move back
    chassis.turnTo(90,true,1000,127,false);//true = right side move back
}
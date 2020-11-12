#include "autons.hpp"
using namespace okapi;

void deploySequence()
{
    deployed = true;
    Elevator.moveRelative(250, 200);
    Intake.moveVelocity(-200);
    pros::delay(500);
    Intake.moveVelocity(0);
}

void auton1()
{
    deploySequence();
}
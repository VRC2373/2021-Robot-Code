#include "autons.hpp"

void deploySequence()
{
    if (!deployed)
    {
        deployed = true;
        Elevator.moveVelocity(-200);
        Intake.moveVelocity(200);
        pros::delay(1250);
        Elevator.moveVelocity(0);
        Intake.moveVelocity(0);
    }
}

void auton1()
{
    deploySequence();
    Elevator.moveVelocity(200);
    Chassis->moveDistance(5_in);
    Flywheel.moveVelocity(200);
    pros::delay(1000);
    Elevator.moveVelocity(0);
    Flywheel.moveVelocity(0);
}

void auton2() {}
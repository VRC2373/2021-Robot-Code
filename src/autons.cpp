#include "autons.hpp"

void deploySequence(bool force)
{
    if (!deployed || force)
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
    Intake.moveVelocity(200);
    Elevator.moveVelocity(200);
    pros::delay(500);
    Intake.moveVelocity(0);
    Chassis->moveDistance(15_in);
    pros::delay(500);
    Flywheel.moveVelocity(200);
    pros::delay(2000);
    Elevator.moveVelocity(0);
    Flywheel.moveVelocity(0);
    Chassis->moveDistance(-5_in);
}

void auton2()
{
    deploySequence(true);
}
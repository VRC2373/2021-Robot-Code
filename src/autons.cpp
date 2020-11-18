#include "autons.hpp"

void deploySequence(bool force)
{
    if (!deployed || force)
    {
        deployed = true;
        Elevator.moveVelocity(-200);
        Flywheel.moveVelocity(200);
        pros::delay(500);
        Elevator.moveVelocity(0);
        Flywheel.moveVelocity(0);
    }
}

void auton1()
{
    deploySequence();
    Intake.moveVelocity(200);
    Elevator.moveVelocity(200);
    pros::delay(500);
    Intake.moveVelocity(0);
    Chassis->moveDistanceAsync(15_in);
    pros::delay(1500);
    Chassis->moveDistance(-1_in);
    Flywheel.moveVelocity(500);
    pros::delay(2000);
    Elevator.moveVelocity(0);
    Flywheel.moveVelocity(0);
    Chassis->moveDistance(-10_in);
}

void auton2()
{
    deploySequence(true);
}

void auton3()
{
    deploySequence();
    Chassis->turnAngle(1.107_deg);
    Chassis->moveDistanceAsync(5.2_ft);
    Elevator.moveVelocity(150);
}
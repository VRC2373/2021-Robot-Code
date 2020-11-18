#include "autons.hpp"

void deploySequence(bool force)
{
    if (!deployed || force)
    {
        deployed = true;
        Intake.moveVelocity(-200);
        Flywheel.moveVelocity(200);
        pros::delay(500);
        Intake.moveVelocity(0);
        Flywheel.moveVelocity(0);
    }
}

void auton1()
{
    deploySequence();
    Elevator.moveVelocity(200);
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
    Inertial.calibrate();
    Inertial.reset();
    deploySequence();
    Elevator.moveVelocity(200);
    Chassis->moveDistance(-1_in);
    Flywheel.moveVelocity(500);
    pros::delay(2000);
    Flywheel.moveVelocity(0);
    Chassis->moveDistance(-10_in);
    Chassis->turnAngle(-180_deg);
    while (Inertial.get() < 178 || Inertial.get() > -178)
        Chassis->getModel()->rotate((Inertial.get() > 0) ? 50 : -50);
    Chassis->moveDistanceAsync(3.5_ft);
    Intake.moveVelocity(200);
    pros::delay(2500);
    Chassis->moveDistance(-1_in);
    Intake.moveVelocity(0);
    Flywheel.moveVelocity(500);
    pros::delay(2000);
    Elevator.moveVelocity(0);
    Flywheel.moveVelocity(0);
}

void auton3()
{
    deploySequence();
    Chassis->turnAngle(1.107_deg);
    Chassis->moveDistanceAsync(5.2_ft);
    Elevator.moveVelocity(150);
}
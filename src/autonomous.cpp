#include "autonomous.hpp"

uint8_t getPins()
{
    unsigned int pins = 0;
    for (int i = 0; i < 8; i++)
        pins |= (pros::ADIDigitalIn(i + 1).get_value() & 1) << i;
    return pins;
};

void deploySequence(bool force)
{
    if (!deployed || force)
    {
        Flywheel.moveVelocity(200);
        pros::delay(400);
        Flywheel.moveVelocity(0);
        deployed = true;
    }
}

void oneBall()
{
    // Chassis->setMaxVelocity(50);
    deploySequence(true);
    Elevator.moveVelocity(500);
    Intake.moveVelocity(75);
    chassis.driveFor(15);
    pros::delay(3000);
    Intake.moveVelocity(0);
    chassis.driveFor(-1);
    Flywheel.moveVelocity(600);
    pros::delay(2000);
    Elevator.moveVelocity(0);
    Flywheel.moveVelocity(0);
    chassis.driveFor(-10);
}

void twoBall()
{
    chassis.setPosition(-63, 17, 270);

    // Back out
    chassis.driveTo(-4 * 12, 17, true);
    deploySequence(true);

    // Drive to goal
    Elevator.moveVelocity(200);
    chassis.driveTo(-5.5 * 12, 0, false, BumperOffset);
    // Chassis->moveDistance(-1_in);

    // Score Ball
    Flywheel.moveVelocity(600);
    pros::delay(750);
    Flywheel.moveVelocity(0);

    // Back out and move to other goal
    chassis.driveTo(-3 * 12, 3 * 12, true);
    Intake.moveVelocity(100);
    chassis.driveTo(-5.5 * 12, 5.5 * 12, false, BumperOffset);
    while (TopOptical.getProximity() < 100)
        ;
    Intake.moveVelocity(0);

    // Score Ball
    Flywheel.moveVelocity(600);
    pros::delay(1500);
    Flywheel.moveVelocity(0);
    Elevator.moveVelocity(0);

    // Back out
    Intake.moveVelocity(-50);
    chassis.driveFor(-10);
    Intake.moveVelocity(0);
}

void twoBallHood()
{
    // chassis.setPosition(-59.5, 12.12, 30);
    // deploySequence(true);
    // chassis.driveTo(-3 * 12, 3 * 12);
    // Chassis->turnToPoint(GoalA);
    // Intake.moveVelocity(200);
    // Elevator.moveVelocity(200);

    // Chassis->moveDistanceAsync(43_in);
    // pros::delay(1500);
    // Chassis->moveDistanceAsync(-1_in);
    // pros::delay(200);
    // Intake.moveVelocity(-200);
    // Flywheel.moveVelocity(600);
    // pros::delay(1500);
    // Chassis->moveDistanceAsync(-10_in);
    // Intake.moveVelocity(0);
    // Elevator.moveVelocity(0);
    // Flywheel.moveVelocity(0);
}

void sortTower()
{
    const bool left = !pros::ADIDigitalIn('H').get_value();
    chassis.setPosition(-56.5, 41, -90);

    chassis.driveTo(-4 * 12, 4 * 12, true);
    deploySequence();
    Flywheel.moveVelocity(-400);
    pros::delay(500);
    Flywheel.moveVelocity(0);
    Intake.moveVelocity(200);
    chassis.driveTo(-5.5 * 12, 5.5 * 12, false, BumperOffset);
    chassis.driveFor(-1);
    Elevator.moveVelocity(200);
    Flywheel.moveVelocity(600);

    BottomOptical.setLedPWM(100);

    if (left)
        while (BottomOptical.getRGB().red < 200)
            pros::delay(20);
    else
        while (BottomOptical.getRGB().blue < 200)
            pros::delay(20);

    Intake.moveVelocity(0);

    pros::delay(100);

    Elevator.moveVelocity(0);
    chassis.driveFor(-10);
    Flywheel.moveVelocity(500);
    Elevator.moveVelocity(200);
    pros::delay(500);
    Flywheel.moveVelocity(0);
    Intake.moveVelocity(0);
    Elevator.moveVelocity(0);
}

void homeRow()
{
    // Chassis->setState({-6_ft + (17_in / 2), 2_ft - (14_in / 2), 90_deg});
    // Chassis->setMaxVelocity(100);

    // // Back out
    // Chassis->moveDistanceAsync(1.25_ft);
    // deploySequence(true);
    // Chassis->waitUntilSettled();

    // // Drive to goal
    // Elevator.moveVelocity(200);
    // Chassis->driveToPoint(GoalD, false, BumperOffset);

    // // Score Ball
    // Flywheel.moveVelocity(500);
    // pros::delay(750);
    // Flywheel.moveVelocity(0);

    // // Back out and move to other goal
    // Chassis->driveToPoint({-3_ft, 3_ft}, true);
    // Intake.moveVelocity(100);
    // Chassis->driveToPoint(GoalA, false, BumperOffset);

    // // Score Ball
    // Flywheel.moveVelocity(500);
    // pros::delay(250);
    // Intake.moveVelocity(0);
    // pros::delay(500);
    // Flywheel.moveVelocity(0);
    // Elevator.moveVelocity(0);

    // // Back out
    // Intake.moveVelocity(-100);
    // Chassis->driveToPoint({-3_ft, 3_ft}, true);
    // Intake.moveVelocity(0);

    // // Drive to the other side of the field
    // Chassis->driveToPoint({-3_ft, -3_ft});
    // Intake.moveVelocity(100);
    // Elevator.moveVelocity(200);
    // Chassis->driveToPoint(GoalG, false, BumperOffset);

    // // Score Ball
    // Flywheel.moveVelocity(500);
    // pros::delay(250);
    // Intake.moveVelocity(0);
    // pros::delay(750);
    // Flywheel.moveVelocity(0);
    // Elevator.moveVelocity(0);

    // // Back out
    // Intake.moveVelocity(-100);
    // Chassis->moveDistance(-10_in);
}
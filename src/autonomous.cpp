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
    Chassis->setMaxVelocity(50);
    deploySequence(true);
    Elevator.moveVelocity(500);
    Intake.moveVelocity(75);
    Chassis->moveDistanceAsync(15_in);
    pros::delay(3000);
    Intake.moveVelocity(0);
    Chassis->moveDistance(-1_in);
    Flywheel.moveVelocity(600);
    pros::delay(2000);
    Elevator.moveVelocity(0);
    Flywheel.moveVelocity(0);
    Chassis->setMaxVelocity(200);
    Chassis->moveDistance(-10_in);
}

void twoBall()
{
    Chassis->setState({-63_in, 17_in, 270_deg});

    // Back out
    Chassis->driveToPoint({-4_ft, 17_in}, true);
    deploySequence(true);

    // Drive to goal
    Elevator.moveVelocity(200);
    Chassis->driveToPoint(GoalD, false, BumperOffset);
    // Chassis->moveDistance(-1_in);

    // Score Ball
    Flywheel.moveVelocity(600);
    pros::delay(750);
    Flywheel.moveVelocity(0);

    // Back out and move to other goal
    Chassis->driveToPoint({-3_ft, 3_ft}, true);
    Intake.moveVelocity(100);
    Chassis->driveToPoint(GoalA, false, BumperOffset);
    while (Optical.getProximity() < 100)
        ;
    Intake.moveVelocity(0);

    // Score Ball
    Flywheel.moveVelocity(600);
    pros::delay(1500);
    Flywheel.moveVelocity(0);
    Elevator.moveVelocity(0);

    // Back out
    Intake.moveVelocity(-50);
    Chassis->moveDistance(-10_in);
    Intake.moveVelocity(0);
}

void twoBallHood()
{
    Chassis->setState({-59.5_in, 12.12_in, 30_deg});
    deploySequence(true);
    Chassis->driveToPoint({-3_ft, 3_ft});
    Chassis->turnToPoint(GoalA);
    Intake.moveVelocity(200);
    Elevator.moveVelocity(200);

    //distance wrong
    Chassis->moveDistanceAsync(44.91_in);
    pros::delay(1500);
    Intake.moveVelocity(0);
    Flywheel.moveVelocity(600);
    pros::delay(1500);
    Chassis->moveDistanceAsync(-10_in);
    Elevator.moveVelocity(0);
    Flywheel.moveVelocity(0);
}

void auton3()
{
    Chassis->setState({5.25_ft, 41_in, 0_deg});

    Chassis->driveToPoint({4_ft, 41_in}, true);
    deploySequence();
    Chassis->turnToPoint(GoalC);
    Elevator.moveVelocity(200);
    Intake.moveVelocity(100);
    Chassis->driveToPoint(GoalC, false, BumperOffset);

    // Score Ball
    Flywheel.moveVelocity(500);

    bool prevVal = false;
    for (int balls = 1; balls <= 3;)
    {
        if (Optical.getProximity() > 100)
        {
            balls++;
            while (Optical.getProximity() > 100)
                pros::delay(20);
        }
    }
    Intake.moveVelocity(0);
    Flywheel.moveVelocity(0);
    Elevator.moveVelocity(0);
    Chassis->moveDistance(-20_in);
    Flywheel.moveVelocity(500);
    Elevator.moveVelocity(200);
    pros::delay(500);
    Flywheel.moveVelocity(0);
    Elevator.moveVelocity(0);
}

void homeRow()
{
    Chassis->setState({-6_ft + (17_in / 2), 2_ft - (14_in / 2), 90_deg});
    Chassis->setMaxVelocity(100);

    // Back out
    Chassis->moveDistanceAsync(1.25_ft);
    deploySequence(true);
    Chassis->waitUntilSettled();

    // Drive to goal
    Elevator.moveVelocity(200);
    Chassis->driveToPoint(GoalD, false, BumperOffset);

    // Score Ball
    Flywheel.moveVelocity(500);
    pros::delay(750);
    Flywheel.moveVelocity(0);

    // Back out and move to other goal
    Chassis->driveToPoint({-3_ft, 3_ft}, true);
    Intake.moveVelocity(100);
    Chassis->driveToPoint(GoalA, false, BumperOffset);

    // Score Ball
    Flywheel.moveVelocity(500);
    pros::delay(250);
    Intake.moveVelocity(0);
    pros::delay(500);
    Flywheel.moveVelocity(0);
    Elevator.moveVelocity(0);

    // Back out
    Intake.moveVelocity(-100);
    Chassis->driveToPoint({-3_ft, 3_ft}, true);
    Intake.moveVelocity(0);

    // Drive to the other side of the field
    Chassis->driveToPoint({-3_ft, -3_ft});
    Intake.moveVelocity(100);
    Elevator.moveVelocity(200);
    Chassis->driveToPoint(GoalG, false, BumperOffset);

    // Score Ball
    Flywheel.moveVelocity(500);
    pros::delay(250);
    Intake.moveVelocity(0);
    pros::delay(750);
    Flywheel.moveVelocity(0);
    Elevator.moveVelocity(0);

    // Back out
    Intake.moveVelocity(-100);
    Chassis->moveDistance(-10_in);
}
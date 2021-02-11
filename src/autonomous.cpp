#include "autonomous.hpp"

void autonSelection()
{
    std::string output;

    uint8_t prevSelection = selectedAuton;
    while (true)
    {
        if (Primary[ControllerDigital::up].changedToPressed())
            selectedAuton++;
        if (Primary[ControllerDigital::down].changedToPressed())
            selectedAuton--;
        if (Primary[ControllerDigital::left].changedToPressed())
            autonSide = LEFT;
        if (Primary[ControllerDigital::right].changedToPressed())
            autonSide = RIGHT;
        if (autons.size() > 1)
            selectedAuton %= autons.size() - 1;

        if (autonSide == LEFT)
            output = "L";
        if (autonSide == RIGHT)
            output = "R";

        // Print to Controller screen
        pros::delay(50);
        Primary.clearLine(2);
        pros::delay(50);
        Primary.setText(2, 0, autons[selectedAuton].name);

        pros::delay(20);
    }
}

void deploySequence(bool force)
{
    if (!deployed || force)
    {
        deployed = true;
        Elevator.moveVelocity(-200);
        Flywheel.moveVelocity(200);
        pros::delay(400);
        Elevator.moveVelocity(0);
        Flywheel.moveVelocity(0);
    }
}

void auton1()
{
    deploySequence(true);
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

// Goal Positions for Odometry
const Point centerGoal = {5.5_ft, 0_in};
const Point leftGoal = {5.6_ft, 5.6_ft};
const Point rightGoal = {5.6_ft, -5.6_ft};

void auton2()
{
    Chassis->setState({5.25_ft, 17_in, 0_deg});

    // Back out
    Chassis->driveToPoint({4_ft, 17_in}, true);
    deploySequence(true);

    // Drive to goal
    Elevator.moveVelocity(200);
    Chassis->driveToPoint(centerGoal, false, BumperOffset);
    Chassis->moveDistance(-1_in);

    // Score Ball
    Flywheel.moveVelocity(500);
    pros::delay(750);
    Flywheel.moveVelocity(0);

    // Back out and move to other goal
    Chassis->driveToPoint({3_ft, 3_ft}, true);
    Intake.moveVelocity(100);
    Chassis->driveToPoint(leftGoal, false, BumperOffset);
    while (Optical.getProximity() < 100)
        ;
    Intake.moveVelocity(0);

    // Score Ball
    Flywheel.moveVelocity(500);
    pros::delay(1500);
    Flywheel.moveVelocity(0);
    Elevator.moveVelocity(0);

    // Back out
    Intake.moveVelocity(-50);
    Chassis->moveDistance(-10_in);
    Intake.moveVelocity(0);
}

void auton3()
{
    Chassis->setState({5.25_ft, 41_in, 0_deg});

    Chassis->driveToPoint({4_ft, 41_in}, true);
    deploySequence();
    Chassis->turnToPoint(leftGoal);
    Elevator.moveVelocity(200);
    Intake.moveVelocity(100);
    Chassis->driveToPoint(leftGoal, false, BumperOffset);

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
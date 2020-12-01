#include "autons.hpp"

const QLength bumperOffset = 6.5_in + .5_ft;

uint8_t getAuton() { return AutoSide.get_value() | (Auto1.get_value() ? 1 : Auto2.get_value() ? 2 : Auto3.get_value() ? 3 : 0) << 1; }

void autonSelection()
{
    const uint8_t numAutons = 3;
    const char *autonNames[numAutons + 1] = {"None", "Score Preload", "Score 2", "Solid Color Corner"};
    char buff[100];
    static uint8_t selection;

    lv_obj_t *autonText = lv_label_create(lv_scr_act(), NULL);
    while (true)
    {
        if (getAuton() != selection)
        {
            selection = getAuton();
            sprintf(buff, "%s%s Selected", ((selection >> 1) >= 2) ? (selection & 1) ? "Right Side " : "Left Side " : "", autonNames[selection >> 1]);
            lv_label_set_text(autonText, buff);
            sprintf(buff, "%s%s", ((selection >> 1) >= 2) ? (selection & 1) ? "R " : "L " : "", autonNames[selection >> 1]);
            Primary.clearLine(2);
            pros::delay(50);
            Primary.setText(2, 0, buff);
            pros::delay(50);
            Primary.rumble(".");
        }
        pros::delay(20);
    }
}

void autonController()
{
    const uint8_t selection = getAuton();
    switch (selection >> 1)
    {
    case 1:
        auton1();
        break;
    case 2:
        auton2(selection & 1);
        break;
    case 3:
        auton3(selection & 1);
        break;
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

void auton2(bool rightSide)
{
    const Point goal1 = {5.5_ft, 0_in};
    const Point goal2 = rightSide ? (Point){5.5_ft, -5.5_ft} : (Point){5.5_ft, 5.5_ft};

    Chassis->setState({5.25_ft, rightSide ? -17_in : 17_in, 0_deg});

    // Back out
    Chassis->driveToPoint({4_ft, rightSide ? -17_in : 17_in}, true);
    deploySequence(true);

    // Drive to goal
    Elevator.moveVelocity(200);
    Chassis->driveToPoint(goal1, false, bumperOffset);
    Chassis->moveDistance(-1_in);

    // Score Ball
    Flywheel.moveVelocity(500);
    pros::delay(750);
    Flywheel.moveVelocity(0);

    // Back out and move to other goal
    Chassis->driveToPoint({3_ft, rightSide ? -3_ft : 3_ft}, true);
    Intake.moveVelocity(200);
    Chassis->driveToPoint(goal2, false, bumperOffset);

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
    Intake.moveVelocity(0);
}

void auton3(bool rightSide)
{
    Chassis->setState({rightSide ? -5.25_ft : 5.25_ft, 17_in, 0_deg});
    const Point goal = rightSide ? (Point){4.5_ft, 5.5_ft} : (Point){4.5_ft, -5.5_ft};

    Chassis->driveToPoint({-2_ft, Chassis->getState().x}, true);
    deploySequence();
    Chassis->turnToPoint(goal);
    Elevator.moveVelocity(200);
    Intake.moveVelocity(200);
    Chassis->driveToPoint(goal, false, bumperOffset);

    // Score Ball
    Flywheel.moveRelative(10.0, 500);

    Elevator.moveVelocity(0);
    Intake.moveVelocity(0);
}

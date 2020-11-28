#include "autons.hpp"

uint8_t getAuton() { return Auto1.get_value() ? 1 : Auto2.get_value() ? 2 : Auto3.get_value() ? 3 : Auto4.get_value() ? 4 : 0; }

void autonSelection()
{
    const uint8_t numAutons = 4;
    const char *autonNames[numAutons + 1] = {"No", "Score Preload", "Score Preload and a Tower", "Score 2", "Not sure"};
    lv_obj_t *scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);
    char buff[100];

    lv_obj_t *autonText = lv_label_create(scr, NULL);
    while (true)
    {
        sprintf(buff, "%s Auton Selected", getAuton() <= numAutons ? autonNames[getAuton()] : "Unknown");
        lv_label_set_text(autonText, buff);
        pros::delay(200);
    }
}

void autonController()
{
    switch (getAuton())
    {
    case 1:
        auton1();
        break;
    case 2:
        auton2();
        break;
    case 3:
        auton3();
        break;
    case 4:
        auton3();
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

void auton2()
{
    // Inertial.calibrate();
    // Inertial.reset();
    deploySequence();
    Elevator.moveVelocity(200);
    Chassis->moveDistance(-1_in);
    Flywheel.moveVelocity(500);
    pros::delay(2000);
    Flywheel.moveVelocity(0);
    Chassis->moveDistance(-10_in);
    Chassis->turnAngle(-180_deg);
    // while (Inertial.get() < 178 || Inertial.get() > -178)
    //     Chassis->getModel()->rotate((Inertial.get() > 0) ? 50 : -50);
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

const QLength bumperOffset = 6.5_in + .5_ft;

void auton3()
{
    const Point goal1 = {5.5_ft, 0_in};
    const Point goal2 = {4.5_ft, 5.5_ft};

    Chassis->setState({5.25_ft, 17_in, 0_deg});

    // Back out
    Chassis->driveToPoint({4_ft, 17_in}, true);
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
    Chassis->driveToPoint({4_ft, 17_in}, true);
    Intake.moveVelocity(200);
    Chassis->driveToPoint(goal2, false, bumperOffset);

    // Score Ball
    Flywheel.moveVelocity(500);
    pros::delay(750);
    Flywheel.moveVelocity(0);
    Intake.moveVelocity(0);
    Elevator.moveVelocity(0);

    // Back out
    Chassis->moveDistance(-10_in);
}

void auton4()
{
    deploySequence();
    Chassis->turnAngle(1.107_deg);
    Chassis->moveDistanceAsync(5.2_ft);
    Elevator.moveVelocity(150);
}

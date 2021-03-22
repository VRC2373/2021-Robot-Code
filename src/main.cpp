#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
    pros::delay(400);
    const uint8_t pins = getPins();
    // Optical.setLedPWM(100);
    if (pros::ADIDigitalIn(1).get_value())
        oneBall();
    else if (pros::ADIDigitalIn(2).get_value())
        twoBall();
    else if (pros::ADIDigitalIn(3).get_value())
        twoBallHood();
    else if (pros::ADIDigitalIn(4).get_value())
        sortTower();
    else if (pros::ADIDigitalIn(5).get_value())
        skills();
    Optical.setLedPWM(0);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
    Optical.setLedPWM(0);
    bool elevatorToggle = false;
    bool tankDrive = pros::ADIDigitalIn(8).get_value();

    if (pros::competition::is_connected())
        deploySequence();

    while (true)
    {
        if (!tankDrive)
            Chassis->getModel()->arcade(Primary.getAnalog(ControllerAnalog::leftY), Primary.getAnalog(ControllerAnalog::rightX));
        else
            Chassis->getModel()->tank(Primary.getAnalog(ControllerAnalog::leftY), Primary.getAnalog(ControllerAnalog::rightY));

        Intake.moveVelocity(
            btnIntakeIn.isPressed()
                ? 200
            : btnIntakeOut.isPressed() || btnFlywheelOut.isPressed()
                ? -200
                : 0);

        if (btnElevatorToggle.changedToPressed())
            elevatorToggle = !elevatorToggle;
        Elevator.moveVelocity(
            btnElevatorOut.isPressed()
                ? -400
            : btnFlywheelOut.isPressed()
                ? 600
            : elevatorToggle && Optical.getProximity() < 100
                ? 300
                : 0);
        Flywheel.moveVelocity(
            btnElevatorOut.isPressed()
                ? -200
            : btnFlywheelOut.isPressed()
                ? 600
                : 0);
        pros::delay(20);
    }
}

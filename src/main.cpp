#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	if (!pros::competition::is_connected)
		Vision.set_wifi_mode(true);
}

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
void competition_initialize()
{
	Vision.set_wifi_mode(false);
	autonSelection();
}

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
	autonController();
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
	lv_obj_t *scr = lv_obj_create(NULL, NULL);
	lv_scr_load(scr);

	lv_obj_t *printout = lv_label_create(scr, NULL);
	bool elevatorToggle = false;

	if (pros::competition::is_connected() && !deployed)
		deploySequence();

	while (true)
	{
		char buf[32];
		sprintf(buf, "IMU: %f", Inertial.get());
		lv_label_set_text(printout, buf);
		Chassis->getModel()->arcade(Primary.getAnalog(ControllerAnalog::leftY), Primary.getAnalog(ControllerAnalog::rightX));

		Intake.moveVelocity(btnIntakeIn.isPressed() ? 200 : btnIntakeOut.isPressed() ? -200 : 0);
		elevatorToggle = btnElevatorToggle.changedToPressed() ? !elevatorToggle : elevatorToggle;
		Elevator.moveVelocity(elevatorToggle || btnFlywheelOut.isPressed() ? 200 : btnElevatorOut.isPressed() ? -200 : 0);
		Flywheel.moveVelocity(btnFlywheelOut.isPressed() ? 500 : btnElevatorOut.isPressed() ? -200 : 0);
		pros::delay(20);
	}
}

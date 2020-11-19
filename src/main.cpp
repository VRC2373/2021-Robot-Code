#include "main.h"

uint8_t autonSelected = 0;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	Inertial.calibrate();
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
	Inertial.calibrate();
	Inertial.reset();

	lv_obj_t *scr = lv_obj_create(NULL, NULL);
	lv_scr_load(scr);

	lv_obj_t *autonText = lv_label_create(scr, NULL);

	while (true)
	{
		autonSelected = Auto1.get_value() ? 1 : Auto2.get_value() ? 2 : Auto3.get_value() ? 3 : 0;
		switch (autonSelected)
		{
		case 0:
			lv_label_set_text(autonText, "No Auton Selected");
			break;
		case 1:
			lv_label_set_text(autonText, "Score Preload Auton Selected");
			break;
		case 2:
			lv_label_set_text(autonText, "Score Preload and a Tower Auton Selected");
			break;
		case 3:
			lv_label_set_text(autonText, "\"Not sure what to call it\" Auton Selected");
			break;
		default:
			lv_label_set_text(autonText, "Unknown Auton Selected");
			break;
		}
		pros::delay(200);
	}
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
	autonSelected = Auto1.get_value() ? 1 : Auto2.get_value() ? 2 : 0;
	switch (autonSelected)
	{
	case 1:
		auton1();
		break;
	case 2:
		auton2();
		break;
	case 3:
		auton2();
		break;
	}
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
		Elevator.moveVelocity(elevatorToggle ? 200 : btnElevatorOut.isPressed() ? -200 : 0);
		Flywheel.moveVelocity(btnFlywheelOut.isPressed() ? 500 : 0);
		pros::delay(20);
	}
}

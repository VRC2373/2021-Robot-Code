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
	// Build Chasis
	ChasisBuilder.withMotors(
					 {15, 14},	// Left motors are 15 & 14
					 {-16, -17} // Right motors are 16 & 17 (reversed)
					 )
		.withDimensions(okapi::AbstractMotor::gearset::green, {{4_in, 10_in}, okapi::imev5GreenTPR});
	// .withOdometry(Inertial);
	Chasis = ChasisBuilder.build();
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
	Inertial.reset();
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
void autonomous() {}

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
	if (pros::competition::is_connected() && !deployed)
		deploySequence();

	while (true)
	{
		Chasis->getModel()->arcade(Primary.getAnalog(ControllerAnalog::leftY), Primary.getAnalog(ControllerAnalog::rightX));

		Intake.moveVelocity(Primary.getDigital(ControllerDigital::R1) ? 200 : Primary.getDigital(ControllerDigital::R2) ? -200 : 0);

		Elevator.moveVelocity(Primary.getDigital(ControllerDigital::L1) || Primary.getDigital(ControllerDigital::L2) ? 200 : Primary.getDigital(ControllerDigital::B) ? -200 : 0);
		Flywheel.moveVelocity(Primary.getDigital(ControllerDigital::L1) ? 200 : 0);
	}
}

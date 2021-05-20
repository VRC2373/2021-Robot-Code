#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() { pros::lcd::initialize(); }

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
void autonomous() {
  Inertial->reset();
  pros::delay(2000);

  // chassis.driveFor2(24);
  // chassis.turnFor(90);

  // BottomOptical.setLedPWM(100);
  // TopOptical.setLedPWM(100);
  // if (!pros::ADIDigitalIn('A').get_value())
  //     oneBall();
  // else if (!pros::ADIDigitalIn('B').get_value())
  //     twoBall();
  // else if (!pros::ADIDigitalIn('C').get_value())
  // twoBallHood();
  // else if (!pros::ADIDigitalIn('D').get_value())
  // sortTower();
  // else if (!pros::ADIDigitalIn('E').get_value())
  //     skills();
  // TopOptical.setLedPWM(0);
  // BottomOptical.setLedPWM(0);

  homeRow();
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
void opcontrol() {
  TopOptical.set_led_pwm(0);
  BottomOptical.set_led_pwm(0);
  bool elevatorToggle = false;
  bool tankDrive = pros::ADIDigitalIn(8).get_value();

  if (pros::competition::is_connected()) deploySequence();

  // Inertial->reset();
  // while (true)
  // {
  //     pros::lcd::print(0, "%.2f", Inertial->get_yaw());
  //     pros::delay(20);
  // }

  while (true) {
    chassis.splitArcade(Primary.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                        Primary.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    // if (!tankDrive)
    // Chassis->getModel()->arcade(Primary.getAnalog(ControllerAnalog::leftY),
    // Primary.getAnalog(ControllerAnalog::rightX)); else
    //     Chassis->getModel()->tank(Primary.getAnalog(ControllerAnalog::leftY),
    //     Primary.getAnalog(ControllerAnalog::rightY));
    btnIntakeIn = Primary.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    btnIntakeOut = Primary.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    btnElevatorToggle =
        Primary.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2);
    btnElevatorOut = Primary.get_digital(pros::E_CONTROLLER_DIGITAL_B);
    btnFlywheelOut = Primary.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    btnDeployBar = Primary.get_digital(pros::E_CONTROLLER_DIGITAL_A);

    LIntake = btnIntakeIn ? 127 : btnIntakeOut || btnElevatorOut ? -127 : 0;
    RIntake = btnIntakeIn ? 127 : btnIntakeOut || btnElevatorOut ? -127 : 0;

    if (btnElevatorToggle) elevatorToggle = !elevatorToggle;

    Elevator = (btnElevatorOut                                       ? -400
                : btnFlywheelOut                                     ? 600
                : elevatorToggle && TopOptical.get_proximity() < 100 ? 300
                                                                     : 0);

    Flywheel = btnElevatorOut ? -42.333 : btnFlywheelOut ? 127 : 0;
    pros::delay(20);
  }
}

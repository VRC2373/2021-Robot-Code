#include "autonomous.hpp"

uint8_t getPins() {
  unsigned int pins = 0;
  for (int i = 0; i < 8; i++)
    pins |= (pros::ADIDigitalIn(i + 1).get_value() & 1) << i;
  return pins;
};

void deploySequence(bool force) {
  if (!deployed || force) {
    Flywheel = 127;
    pros::delay(400);
    Flywheel = 0;
    deployed = true;
  }
}

void oneBall() {
  // Chassis->setMaxVelocity(50);
  // deploySequence(true);
  // Elevator.moveVelocity(500);
  // Intake.moveVelocity(75);
  // chassis.driveFor(15);
  // pros::delay(3000);
  // Intake.moveVelocity(0);
  // chassis.driveFor(-1);
  // Flywheel.moveVelocity(600);
  // pros::delay(2000);
  // Elevator.moveVelocity(0);
  // Flywheel.moveVelocity(0);
  // chassis.driveFor(-10);
}

void twoBall() {
  // chassis.setPosition(-63, 17, 270);

  // // Back out
  // chassis.driveTo(-4 * 12, 17, true);
  // deploySequence(true);

  // // Drive to goal
  // Elevator.moveVelocity(200);
  // chassis.driveTo(-5.5 * 12, 0, false, BumperOffset);
  // // Chassis->moveDistance(-1_in);

  // // Score Ball
  // Flywheel.moveVelocity(600);
  // pros::delay(750);
  // Flywheel.moveVelocity(0);

  // // Back out and move to other goal
  // chassis.driveTo(-3 * 12, 3 * 12, true);
  // Intake.moveVelocity(100);
  // chassis.driveTo(-5.5 * 12, 5.5 * 12, false, BumperOffset);
  // while (TopOptical.getProximity() < 100)
  //     ;
  // Intake.moveVelocity(0);

  // // Score Ball
  // Flywheel.moveVelocity(600);
  // pros::delay(1500);
  // Flywheel.moveVelocity(0);
  // Elevator.moveVelocity(0);

  // // Back out
  // Intake.moveVelocity(-50);
  // chassis.driveFor(-10);
  // Intake.moveVelocity(0);
}

void twoBallHood() {
  chassis.setPosition(-59.5, -12.12, 153);
  deploySequence(true);
  chassis.driveTo(-3 * 12, -3 * 12);
  chassis.turnTo(GoalA);
  LIntake = 127;
  RIntake = 127;
  Elevator = 43;

  chassis.driveFor2(43);
  chassis.driveFor2(-1);
  pros::delay(200);
  LIntake = -127;
  RIntake = -127;
  Flywheel = 127;
  pros::delay(1500);
  chassis.driveFor2(-10);
  LIntake = 0;
  RIntake = 0;
  Elevator = 0;
  Flywheel = 0;
}

void sortTower() {
  // const bool left = !pros::ADIDigitalIn('H').get_value();
  // chassis.setPosition(-56.5, 41, -90);

  // chassis.driveTo(-4 * 12, 4 * 12, true);
  // deploySequence();
  // Flywheel.moveVelocity(-400);
  // pros::delay(500);
  // Flywheel.moveVelocity(0);
  // Intake.moveVelocity(200);
  // chassis.driveTo(-5.5 * 12, 5.5 * 12, false, BumperOffset);
  // chassis.driveFor(-1);
  // Elevator.moveVelocity(200);
  // Flywheel.moveVelocity(600);

  // BottomOptical.setLedPWM(100);

  // if (left)
  //     while (BottomOptical.getRGB().red < 200)
  //         pros::delay(20);
  // else
  //     while (BottomOptical.getRGB().blue < 200)
  //         pros::delay(20);

  // Intake.moveVelocity(0);

  // pros::delay(100);

  // Elevator.moveVelocity(0);
  // chassis.driveFor(-10);
  // Flywheel.moveVelocity(500);
  // Elevator.moveVelocity(200);
  // pros::delay(500);
  // Flywheel.moveVelocity(0);
  // Intake.moveVelocity(0);
  // Elevator.moveVelocity(0);
}

void homeRow() {
  chassis.setPosition(-59.5f, 12.12f, 27.0f);
  deploySequence(true);
  puts("driving to go to goal a");
  chassis.driveTo(-36.0f, 36.0f);
  puts("point to goal a");
  chassis.turnTo(GoalA);
  LIntake = 127;
  RIntake = 127;
  Elevator = 43;

  puts("drive to goal a");
  chassis.driveFor2(43.0f);
  puts("back up 1\"");
  chassis.driveFor2(-1.0f);
  pros::delay(200);
  LIntake = -127;
  RIntake = -127;
  Flywheel = 127;

  puts("drive back to go to goal a");
  chassis.driveTo(-36.0f, 36.0f, true);
  LIntake = 0;
  RIntake = 0;
  Elevator = 0;
  Flywheel = 0;
  chassis.driveTo(-36.0f, -36.0f);

  LIntake = 127;
  RIntake = 127;
  Elevator = 43;
  chassis.turnTo(GoalH);

  chassis.driveFor2(43.0f);
  chassis.driveFor2(-1.0f);
  pros::delay(200);
  LIntake = -127;
  RIntake = -127;
  Flywheel = 127;
  chassis.driveFor2(-10.0f);
}
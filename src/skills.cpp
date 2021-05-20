#include "autonomous.hpp"

void skills() {
  // Starts next to the bottom-left wall on the field
  chassis.setPosition(80.5, -36, 90);
  chassis.driveTo(36, -36);
  chassis.driveTo(36, 36);
  chassis.driveTo(-36, 36);
  chassis.driveTo(-36, -36);
  // Chassis->driveToPoint({-6_ft + 8.5_in, -3_ft}, true);
  // Chassis->setMaxVelocity(150);

  // // Deploy before doing anything
  // deploySequence();

  // // Intake ball while moving forward
  // Intake.moveVelocity(100);
  // Elevator.moveVelocity(200);
  // Chassis->driveToPoint({-3_ft, -3_ft}, false);
  // Intake.moveVelocity(0);

  // // Drive to Goal G
  // Chassis->driveToPoint(GoalG, false, BumperOffset);
  // Flywheel.moveVelocity(500);
  // Intake.moveVelocity(100);
  // while (Optical.getProximity() < 100 || Optical.getRGB().blue < 200)
  // {
  //     pros::delay(20);
  // }
  // Flywheel.moveVelocity(0);
  // pros::delay(500);
  // Intake.moveVelocity(0);
  // Flywheel.moveVelocity(400);
  // Chassis->driveToPoint({-2_ft, -2_ft}, true);
  // Intake.moveVelocity(100);
  // Chassis->driveToPoint({0_ft, -1_ft});
}
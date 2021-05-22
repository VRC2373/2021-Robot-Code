#include "autonomous.hpp"

uint8_t getPins() {
  unsigned int pins = 0;
  for (int i = 0; i < 8; i++)
    pins |= (pros::ADIDigitalIn(i + 1).get_value() & 1) << i;
  return pins;
};

void deploySequence(bool force) {
  if (!deployed || force) {
    Flywheel.moveVelocity(200);
    pros::delay(400);
    Flywheel.moveVelocity(0);
    deployed = true;
  }
}

void oneBall() {
  Chassis->setMaxVelocity(50);
  deploySequence(true);
  Elevator.moveVelocity(500);
  Intake.moveVelocity(75);
  Chassis->moveDistanceAsync(15_in);
  pros::delay(3000);
  Intake.moveVelocity(0);
  Chassis->moveDistance(-1_in);
  Flywheel.moveVelocity(600);
  pros::delay(2000);
  Elevator.moveVelocity(0);
  Flywheel.moveVelocity(0);
  Chassis->setMaxVelocity(200);
  Chassis->moveDistance(-10_in);
}

void twoBall() {
  Chassis->setState({-63_in, 17_in, 270_deg});

  // Back out
  Chassis->driveToPoint({-4_ft, 17_in}, true);
  deploySequence(true);

  // Drive to goal
  Elevator.moveVelocity(200);
  Chassis->driveToPoint(GoalD, false, BumperOffset);
  // Chassis->moveDistance(-1_in);

  // Score Ball
  Flywheel.moveVelocity(600);
  pros::delay(750);
  Flywheel.moveVelocity(0);

  // Back out and move to other goal
  Chassis->driveToPoint({-3_ft, 3_ft}, true);
  Intake.moveVelocity(100);
  Chassis->driveToPoint(GoalA, false, BumperOffset);
  while (TopOptical.getProximity() < 100)
    ;
  Intake.moveVelocity(0);

  // Score Ball
  Flywheel.moveVelocity(600);
  pros::delay(1500);
  Flywheel.moveVelocity(0);
  Elevator.moveVelocity(0);

  // Back out
  Intake.moveVelocity(-50);
  Chassis->moveDistance(-10_in);
  Intake.moveVelocity(0);
}

void twoBallHood() {
  Chassis->setMaxVelocity(150);
  Chassis->setState({-59.5_in, 12.12_in, 30_deg});
  deploySequence(true);
  Chassis->driveToPoint({-3_ft, 3_ft});
  Chassis->turnToPoint(GoalA);
  Intake.moveVelocity(200);
  Elevator.moveVelocity(200);

  Chassis->moveDistanceAsync(40_in);
  pros::delay(1500);
  Chassis->moveDistanceAsync(-1_in);
  pros::delay(200);
  Intake.moveVelocity(-200);
  Flywheel.moveVelocity(600);
  pros::delay(3500);
  Chassis->moveDistanceAsync(-10_in);
  Intake.moveVelocity(0);
  Elevator.moveVelocity(0);
  Flywheel.moveVelocity(0);
}

void twoBallHoodButRightSide() {
  Chassis->setState({-59.5_in, -12.12_in, 153_deg});
  deploySequence(true);
  Chassis->driveToPoint({-3_ft, -3_ft});
  Chassis->turnToPoint(GoalG);
  Intake.moveVelocity(200);
  Elevator.moveVelocity(200);

  Chassis->moveDistanceAsync(43_in);
  pros::delay(1500);
  Chassis->moveDistanceAsync(-1_in);
  pros::delay(200);
  Intake.moveVelocity(-200);
  Flywheel.moveVelocity(600);
  pros::delay(1500);
  Chassis->moveDistanceAsync(-10_in);
  Intake.moveVelocity(0);
  Elevator.moveVelocity(0);
  Flywheel.moveVelocity(0);
}

void sortTower() {
  Chassis->setState({-56.5_in, 41_in, -90_deg});

  Chassis->driveToPoint({-4_ft, 4_ft}, true);
  deploySequence();
  Flywheel.moveVelocity(-400);
  pros::delay(500);
  Flywheel.moveVelocity(0);
  Intake.moveVelocity(200);
  Chassis->driveToPoint(GoalA, false, BumperOffset);
  Chassis->moveDistance(-1_in);
  Elevator.moveVelocity(200);
  Flywheel.moveVelocity(600);

  BottomOptical.setLedPWM(100);
  // for (int balls = 0; balls < 2; balls++)
  // {
  if (pros::ADIDigitalIn(8).get_value())
    while (BottomOptical.getRGB().red < 200) pros::delay(20);
  else
    while (BottomOptical.getRGB().blue < 200) pros::delay(20);
  // while (Optical.getProximity() <= 100)
  //     pros::delay(20);
  // }

  Intake.moveVelocity(0);

  pros::delay(1500);

  // if (pros::ADIDigitalIn(8).get_value())
  //     while (TopOptical.getRGB().red < 200)
  //         pros::delay(20);
  // else
  //     while (TopOptical.getRGB().blue < 200)
  //         pros::delay(20);

  Elevator.moveVelocity(0);
  Flywheel.moveVelocity(0);
  Chassis->moveDistance(-10_in);
  // Flywheel.moveVelocity(500);
  Elevator.moveVelocity(-200);
  pros::delay(500);
  Flywheel.moveVelocity(0);
  Intake.moveVelocity(0);
  Elevator.moveVelocity(0);
}

void sortRightTower() {
  Chassis->setState({-56.5_in, -41_in, -90_deg});

  Chassis->driveToPoint({-4_ft, -4_ft}, true);
  deploySequence();
  Flywheel.moveVelocity(-400);
  pros::delay(500);
  Flywheel.moveVelocity(0);
  Intake.moveVelocity(200);
  Chassis->driveToPoint(GoalG, false, BumperOffset);
  Chassis->moveDistance(-1_in);
  Elevator.moveVelocity(200);
  Flywheel.moveVelocity(600);

  BottomOptical.setLedPWM(100);
  if (pros::ADIDigitalIn(8)
          .get_value())  // cum dumpster // Thank you Jonathon...
    while (BottomOptical.getRGB().red < 200) pros::delay(20);
  else
    while (BottomOptical.getRGB().blue < 200) pros::delay(20);

  Intake.moveVelocity(0);

  pros::delay(1500);

  Elevator.moveVelocity(0);
  Flywheel.moveVelocity(0);
  Chassis->moveDistance(-10_in);
  Elevator.moveVelocity(-200);
  pros::delay(500);
  Flywheel.moveVelocity(0);
  Intake.moveVelocity(0);
  Elevator.moveVelocity(0);
}

void homeRow() {
  Chassis->setState({-59.5_in, 12.12_in, 30_deg});
  deploySequence(true);
  Chassis->moveDistance(25_in);
  pros::delay(100);
  Chassis->turnToPoint(GoalA);
  Intake.moveVelocity(200);
  Elevator.moveVelocity(200);

  // Chassis->driveToPoint(GoalA, false, BumperOffset);
  Chassis->moveDistanceAsync(23_in);
  pros::delay(900);
  Chassis->moveDistanceAsync(-1_in);
  Intake.moveVelocity(-200);
  Flywheel.moveVelocity(600);
  pros::delay(1400);
  Intake.moveVelocity(0);
  Elevator.moveVelocity(0);
  Flywheel.moveVelocity(0);

  // Allign with wall
  Chassis->moveDistance(-20_in);
  Chassis->turnAngle(-135_deg);
  Chassis->moveDistanceAsync(-40_in);
  pros::delay(1300);
  Chassis->moveDistance(8.2_ft);
  // pros::delay(100);
  Chassis->turnAngle(-135_deg);
  // Intake.moveVelocity(200);
  // Elevator.moveVelocity(200);

  Chassis->moveDistanceAsync(-100_m);
  // pros::delay(900);
  // Chassis->moveDistance(20_in);
  // Chassis->moveDistanceAsync(-1_in);
  // Intake.moveVelocity(-200);
  // Flywheel.moveVelocity(600);
  // pros::delay(1100);
  // Intake.moveVelocity(0);
  // Elevator.moveVelocity(0);
  // Flywheel.moveVelocity(0);

  // Chassis->moveDistanceAsync(-10_in);
}
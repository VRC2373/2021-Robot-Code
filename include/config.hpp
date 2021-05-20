#pragma once
#include "chassis.hpp"

static pros::Optical TopOptical(1);
static pros::Optical BottomOptical(2);
static pros::Imu *Inertial = new pros::Imu(21);

static pros::Motor LIntake(18, true);
static pros::Motor RIntake(8);
static pros::Motor Elevator(7, pros::E_MOTOR_GEARSET_06, false,
                            pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor Flywheel(16, pros::E_MOTOR_GEARSET_06, false,
                            pros::E_MOTOR_ENCODER_ROTATIONS);

// Controller Setup
static bool btnIntakeIn;
static bool btnIntakeOut;
static bool btnElevatorToggle;
static bool btnElevatorOut;
static bool btnFlywheelOut;
static bool btnDeployBar;

static pros::Controller Primary(pros::E_CONTROLLER_MASTER);

static std::vector<pros::Motor> driveMotors{pros::Motor(19, true),
                                            pros::Motor(20), pros::Motor(9),
                                            pros::Motor(10, true)};

static Chassis chassis(driveMotors, 4.0f, 1.5f, 1.0f, Inertial);

static bool deployed = false;

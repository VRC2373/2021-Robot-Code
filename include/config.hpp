#pragma once
#include "okapi/api.hpp"
#include "chassis.hpp"
using namespace okapi;

static OpticalSensor TopOptical(1);
static OpticalSensor BottomOptical(2);
static pros::Imu Inertial(11);

// Actuator Setup
static MotorGroup Intake({Motor(-18), Motor(8)});
static Motor Elevator(7, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
static Motor Flywheel(16, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::rotations);

// Controller Setup
static Controller Primary(ControllerId::master);
static ControllerButton btnIntakeIn(Primary[ControllerDigital::R1]);
static ControllerButton btnIntakeOut(Primary[ControllerDigital::R2]);
static ControllerButton btnElevatorToggle(Primary[ControllerDigital::L2]);
static ControllerButton btnElevatorOut(Primary[ControllerDigital::B]);
static ControllerButton btnFlywheelOut(Primary[ControllerDigital::L1]);
static ControllerButton btnDeployBar(Primary[ControllerDigital::A]);

static pros::Controller Main(pros::E_CONTROLLER_MASTER);

// Chasis Setup
// static std::shared_ptr<OdomChassisController> Chassis =
//     ChassisControllerBuilder()
//         .withMotors(
//             {-19, 20}, // Left motors are 15 & 14
//             {9, -10}   // Right motors are 16 & 17 (reversed)
//             )
//         .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.375_in}, imev5GreenTPR})
//         .withGains({1, 0, 0}, {1, 0, 0})
//         .withOdometry(StateMode::CARTESIAN)
//         .buildOdometry();

static std::vector<pros::Motor> driveMotors{
    pros::Motor(19, true), pros::Motor(20),
    pros::Motor(9), pros::Motor(10, true)};

static Chassis chassis(driveMotors, 4.0f, 1.5f, 1.0f, &Inertial);

static bool deployed = false;

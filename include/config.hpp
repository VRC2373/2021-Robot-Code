#pragma once
#include "okapi/api.hpp"
using namespace okapi;

static OpticalSensor TopOptical(1);
static OpticalSensor BottomOptical(2);
static IMU Inertial(11, IMUAxes::x);

// Actuator Setup
static MotorGroup Intake({Motor(-18), Motor(8)});
static Motor Elevator(7, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::rotations);
static Motor Flywheel(16, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::rotations);

// Controller Setup
static Controller Primary(ControllerId::master);
static ControllerButton btnIntakeIn(Primary[ControllerDigital::R1]);
static ControllerButton btnIntakeOut(Primary[ControllerDigital::R2]);
static ControllerButton btnElevatorToggle(Primary[ControllerDigital::L2]);
static ControllerButton btnElevatorOut(Primary[ControllerDigital::B]);
static ControllerButton btnFlywheelOut(Primary[ControllerDigital::L1]);

// Chasis Setup
static std::shared_ptr<OdomChassisController> Chassis =
    ChassisControllerBuilder()
        .withMotors(
            {-19, 20}, // Left motors are 15 & 14
            {9, -10}   // Right motors are 16 & 17 (reversed)
            )
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 11_in}, imev5GreenTPR})
        // .withGains({3, 0, 0}, {0, 0, 0})
        .withOdometry(StateMode::CARTESIAN)
        .buildOdometry();

static bool deployed = false;

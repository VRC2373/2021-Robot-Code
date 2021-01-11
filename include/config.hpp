#pragma once
#include "okapi/api.hpp"
using namespace okapi;

static pros::ADIDigitalIn AutoSide('A');
static pros::ADIDigitalIn Auto1('B');
static pros::ADIDigitalIn Auto2('C');
static pros::ADIDigitalIn Auto3('D');
static pros::ADIDigitalIn Auto4('E');
static pros::ADIDigitalIn Auto5('F');

static OpticalSensor Optical(9);

// Chasis Setup
static std::shared_ptr<OdomChassisController> Chassis =
    ChassisControllerBuilder()
        .withMotors(
            {15, 14},  // Left motors are 15 & 14
            {-16, -17} // Right motors are 16 & 17 (reversed)
            )
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 10_in}, imev5GreenTPR})
        .withOdometry(StateMode::CARTESIAN)
        .buildOdometry();

// Actuator Setup
static MotorGroup Intake({Motor(11, true, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::rotations), Motor(20, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::rotations)});
static Motor Elevator(-12);
static Motor Flywheel(10, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::rotations);

// Controller Setup
static Controller Primary(ControllerId::master);
static ControllerButton btnIntakeIn(Primary[ControllerDigital::R1]);
static ControllerButton btnIntakeOut(Primary[ControllerDigital::R2]);
static ControllerButton btnElevatorToggle(Primary[ControllerDigital::L2]);
static ControllerButton btnElevatorOut(Primary[ControllerDigital::B]);
static ControllerButton btnFlywheelOut(Primary[ControllerDigital::L1]);

static bool deployed = false;
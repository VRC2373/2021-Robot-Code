#pragma once
#include "okapi/api.hpp"
using namespace okapi;

static IMU Inertial(19, IMUAxes::z);
static pros::Vision Vision(6, pros::E_VISION_ZERO_CENTER);

static pros::ADIDigitalIn Auto1('A');
static pros::ADIDigitalIn Auto2('B');
static pros::ADIDigitalIn Auto3('C');

static std::shared_ptr<ChassisController> Chassis =
    ChassisControllerBuilder()
        .withMotors(
            {15, 14},  // Left motors are 15 & 14
            {-16, -17} // Right motors are 16 & 17 (reversed)
            )
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 10_in}, imev5GreenTPR})
        .build();

static MotorGroup Intake({Motor(-11), Motor(20)});
static Motor Elevator(-12);
static Motor Flywheel(10, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::rotations);

// Controller Setup
static Controller Primary(ControllerId::master);
static ControllerButton btnIntakeIn(ControllerDigital::R1);
static ControllerButton btnIntakeOut(ControllerDigital::R2);
static ControllerButton btnElevatorToggle(ControllerDigital::L2);
static ControllerButton btnElevatorOut(ControllerDigital::B);
static ControllerButton btnFlywheelOut(ControllerDigital::L1);

static bool deployed = false;
static uint8_t autonSelected = 0;
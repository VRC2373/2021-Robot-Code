#pragma once
#include "okapi/api.hpp"
using namespace okapi;

static Controller Primary(ControllerId::master);

static IMU Inertial(19, IMUAxes::z);

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

static bool deployed = false;
#pragma once
#include "okapi/api.hpp"
using namespace okapi;

static IMU Inertial(19, IMUAxes::z);
static pros::Vision Vision(6, pros::E_VISION_ZERO_CENTER);

static pros::ADIDigitalIn AutoSide('A');
static pros::ADIDigitalIn Auto1('B');
static pros::ADIDigitalIn Auto2('C');
static pros::ADIDigitalIn Auto3('D');

// Chasis Setup
static std::shared_ptr<OdomChassisController> Chassis =
    ChassisControllerBuilder()
        .withMotors(
            {15, 14},  // Left motors are 15 & 14
            {-16, -17} // Right motors are 16 & 17 (reversed)
            )
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 10_in}, imev5GreenTPR})
        // .withClosedLoopControllerTimeUtil(__DBL_MAX__, 5.0, 250_ms)
        // .withGains(
        //     {0.008, 0, 0.0001}, // Distance controller gains
        //     {0.001, 0, 0.0001}, // Turn controller gains
        //     {0.0001, 0, 0.0001} // Angle controller gains (helps drive straight)
        //     )
        .withMaxVelocity(100)
        .withLogger(
            std::make_shared<Logger>(
                TimeUtilFactory::createDefault().getTimer(), // It needs a Timer
                "/ser/sout",                                 // Output to the PROS terminal
                Logger::LogLevel::debug                      // Most verbose log level
                ))
        .withOdometry()
        .buildOdometry();

// Actuator Setup
static MotorGroup Intake({Motor(-11), Motor(20)});
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
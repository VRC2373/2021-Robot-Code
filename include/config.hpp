#pragma once
#include "api.h"
#include "okapi/api.hpp"
using namespace okapi;

// static pros::Controller Primary(pros::E_CONTROLLER_MASTER);

// static pros::Motor LF(15, false);
// static pros::Motor LB(14, false);

// static pros::Motor RF(16, true);
// static pros::Motor RB(17, true);

// static pros::Motor LI(11, true);
// static pros::Motor RI(20, false);

// static pros::Motor Elevator(12, true);
// static pros::Motor Flywheel(10, false);

// static pros::Imu Inertial(19);

static okapi::Controller Primary(okapi::ControllerId::master);

static okapi::IMU Inertial(19, okapi::IMUAxes::z);

static okapi::ChassisControllerBuilder ChasisBuilder = okapi::ChassisControllerBuilder();
static std::shared_ptr<okapi::ChassisController> Chasis;

static Motor LeftIntake(-11);
static Motor RightIntake(20);
static MotorGroup Intake({LeftIntake, RightIntake});
static Motor Elevator(-12);
static Motor Flywheel(10);

static bool deployed = false;
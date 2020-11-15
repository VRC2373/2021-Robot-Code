#pragma once
#include "okapi/api.hpp"
using namespace okapi;

static Controller Primary(ControllerId::master);

static IMU Inertial(19, IMUAxes::z);

static ChassisControllerBuilder ChassisBuilder = ChassisControllerBuilder();
static std::shared_ptr<ChassisController> Chassis;

static MotorGroup Intake({Motor(-11), Motor(20)});
static Motor Elevator(-12);
static Motor Flywheel(10);

static bool deployed = false;
#pragma once
#include "api.h"
#include "okapi/api.hpp"

static pros::Controller Primary(pros::E_CONTROLLER_MASTER);

static pros::Motor LF(15, false);
static pros::Motor LB(14, false);

static pros::Motor RF(16, true);
static pros::Motor RB(17, true);

static pros::Motor LI(11, true);
static pros::Motor RI(20, false);

static pros::Motor Elevator(12, true);
static pros::Motor Flywheel(10, false);

static pros::Imu Inertial(19);

static okapi::ChassisControllerBuilder Chasis = okapi::ChassisControllerBuilder();

static bool deployed = false;
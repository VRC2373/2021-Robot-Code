#pragma once
#include "api.h"

static pros::Controller Primary(pros::E_CONTROLLER_MASTER);

static pros::Motor LF(15, false);
static pros::Motor LB(14, false);

static pros::Motor RF(16, true);
static pros::Motor RB(17, true);

static pros::Motor LI(11, false);
static pros::Motor RI(20, true);

static pros::Motor Elevator(12, true);
static pros::Motor Flywheel(10, false);

static pros::Imu Intertial(19);
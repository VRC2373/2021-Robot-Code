#pragma once
#include "api.h"

pros::Controller Primary(pros::E_CONTROLLER_MASTER);

pros::Motor LF(15, false);
pros::Motor LB(14, false);

pros::Motor RF(16, true);
pros::Motor RB(17, true);

pros::Motor LI(11, false);
pros::Motor RI(20, true);

pros::Motor Elevator(12, true);
pros::Motor Flywheel(10, false);

pros::Imu Intertial(19);

pros::Mutex MDrivebase;
pros::Mutex MIntake;
pros::Mutex MElevator;
pros::Mutex MFlywheel;
pros::Mutex MInertial;
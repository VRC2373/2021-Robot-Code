#pragma once
#include "api.h"
#include "okapi/api.hpp"
#include "config.hpp"

using namespace okapi;

uint8_t getAuton();
void autonSelection();
void autonController();

void deploySequence(bool force = false);

void auton1();
void auton2(bool leftSide = true);
void auton3(bool leftSide = true);

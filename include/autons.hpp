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
void auton2(bool rightSide = false);
void auton3(bool rightSide = false);
void homeRow(bool rightSide = false);
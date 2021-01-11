#pragma once
#include "api.h"
#include "okapi/api.hpp"
#include "config.hpp"

using namespace okapi;

const QLength BumperOffset = 6.5_in + .5_ft;
const Point GoalA = {-5.5_ft, 5.5_ft};
const Point GoalB = {0_ft, 5.5_ft};
const Point GoalC = {5.5_ft, 5.5_ft};
const Point GoalD = {-5.5_ft, 0_ft};
const Point GoalE = {0_ft, 0_ft};
const Point GoalF = {5.5_ft, 0_ft};
const Point GoalG = {-5.5_ft, -5.5_ft};
const Point GoalH = {0_ft, -5.5_ft};
const Point GoalI = {5.5_ft, -5.5_ft};

uint8_t getAuton();
void autonSelection();
void runAuton();

void deploySequence(bool force = false);

void auton1();
void auton2(bool rightSide = false);
void auton3(bool rightSide = false);
void homeRow(bool rightSide = false);

void skills();
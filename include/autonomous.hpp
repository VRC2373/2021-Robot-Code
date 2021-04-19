#pragma once
#include "api.h"
#include "okapi/api.hpp"
#include "config.hpp"

using namespace okapi;

enum side
{
    LEFT,
    RIGHT,
    NEITHER
};

const QLength BumperOffset = 9.5_in;
const Point GoalA = {-5.5_ft, 5.5_ft};
const Point GoalB = {0_ft, 5.5_ft};
const Point GoalC = {5.5_ft, 5.5_ft};
const Point GoalD = {-5.5_ft, 0_ft};
const Point GoalE = {0_ft, 0_ft};
const Point GoalF = {5.5_ft, 0_ft};
const Point GoalG = {-5.5_ft, -5.5_ft};
const Point GoalH = {0_ft, -5.5_ft};
const Point GoalI = {5.5_ft, -5.5_ft};

uint8_t getPins();

void deploySequence(bool force = false);

void oneBall();
void twoBall();
void twoBallHood();
void twoBallHoodButRightSide();
void sortTower();
void sortRightTower();
void homeRow();

void skills();

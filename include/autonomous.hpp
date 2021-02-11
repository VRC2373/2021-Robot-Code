#pragma once
#include "api.h"
#include "okapi/api.hpp"
#include "config.hpp"

using namespace okapi;

struct auton
{
    const std::string name;
    void (*run)();
};

enum side
{
    LEFT,
    RIGHT,
    NEITHER
};

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

static uint8_t selectedAuton = 0;
static side autonSide = NEITHER;
void autonSelection();

void deploySequence(bool force = false);

void auton1();
void auton2();
void auton3();
void homeRow();

void skills();

static std::vector<auton> autons{
    {"None", [] {}},
    {"Auton 1", auton1},
    {"Auton 2", auton2},
    {"Auton 3", auton3},
    {"Home Row", homeRow},
    {"Skills", skills}};
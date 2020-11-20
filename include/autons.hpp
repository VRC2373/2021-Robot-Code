#pragma once
#include "api.h"
#include "okapi/api.hpp"
#include "config.hpp"

using namespace okapi;

void autonSelection();

void deploySequence(bool force = false);

const char *autonNames[] = {"No", "Score Preload", "Score Preload and a Tower", "\"Not sure what to call it\""};

void auton1();
void auton2();
void auton3();
void auton4();

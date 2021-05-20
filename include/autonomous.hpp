#pragma once
#include "api.h"
#include "config.hpp"

enum side { LEFT, RIGHT, NEITHER };

constexpr float halfWidth = 7.0f;
constexpr float backOffset = 6.0f;
constexpr float BumperOffset = 9.5f;
const Point GoalA = {-66.0f, 66.0f};
const Point GoalB = {0.0f, 66.0f};
const Point GoalC = {66.0f, 66.0f};
const Point GoalD = {-66.0f, 0.0f};
const Point GoalE = {0.0f, 0.0f};
const Point GoalF = {66.0f, 0.0f};
const Point GoalG = {-66.0f, -66.0f};
const Point GoalH = {0.0f, -66.0f};
const Point GoalI = {66.0f, -66.0f};

uint8_t getPins();

void deploySequence(bool force = false);

void oneBall();
void twoBall();
void twoBallHood();
void sortTower();
void homeRow();

void skills();

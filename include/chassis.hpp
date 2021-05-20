#pragma once
#include "api.h"
#include "vector"

struct Point {
  float x;
  float y;
};

class Chassis {
 public:
  Chassis(std::vector<pros::Motor> drive_motors, float wheel_radius,
          float p_turn, float p_drive, pros::Imu *imu = nullptr);
  void setPosition(float x, float y, float θ);
  void setPosition(Point p, float θ);
  void driveFor(float in);
  void driveFor2(float in);
  void turnFor(float θ);
  void turnTo(float θ);
  void turnTo(float x, float y);
  void turnTo(Point p);
  void driveTo(float x, float y, bool backwards = false, float offset = 0.0f);
  void driveTo(Point p, bool backwards = false, float offset = 0.0f);

  void splitArcade(int x, int θ);
  void tank(int l, int r);

  bool useSquareInputs = false;

  void setSpeeds(int l, int r);

 private:
  // float m_turn_radius;
  // x and y in inches, theta in degrees
  float m_x = 0.0f, m_y = 0.0f, m_θ = 0.0f;
  // float m_dx, m_dy, m_dθ;
  float m_p_drive, m_p_turn;
  float m_r_wheel;
  std::vector<pros::Motor> m_drive_motors;
  pros::Controller *m_controller;
  pros::Imu *m_imu;
};
#include "chassis.hpp"

#include "algorithm"
#include "climits"
#include "cmath"

using namespace pros::literals;

Chassis::Chassis(std::vector<pros::Motor> drive_motors, float wheel_radius,
                 float p_drive, float p_turn, pros::Imu* imu)
    : m_drive_motors{drive_motors},
      m_r_wheel{wheel_radius},
      m_imu{imu},
      m_p_drive{p_drive},
      m_p_turn{p_turn} {
  for (int i = 0; i < m_drive_motors.size(); i++)
    m_drive_motors[i].set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
}

void Chassis::setPosition(float x, float y, float θ) {
  m_x = x;
  m_y = y;
  m_θ = θ;
}

void Chassis::setPosition(Point p, float θ) {
  m_x = p.x;
  m_y = p.y;
  m_θ = θ;
}

void Chassis::driveTo(float x, float y, bool backwards, float offset) {
  if (backwards)
    turnFor(m_θ + std::atan2(y - m_y, x - m_x));
  else
    turnTo(x, y);
  driveFor2((backwards ? -1 : 1) * (std::sqrt(x * x + y * y) - offset));
}

void Chassis::driveTo(Point p, bool backwards, float offset) {
  driveTo(p.x, p.y, backwards, offset);
}

void Chassis::turnTo(float x, float y) {
  turnFor(m_θ - std::atan2(y - m_y, x - m_x));
}

void Chassis::turnTo(Point p) { turnTo(p.x, p.y); }

void Chassis::turnTo(float θ) { turnFor(m_θ - θ); }

void Chassis::driveFor(float in) {
  float err = in, tot_p, tot_v;
  for (int i = 0; i < m_drive_motors.size(); i++)
    m_drive_motors[i].set_zero_position(0);
  do {
    tot_p = tot_v = 0.0f;
    for (int i = 0; i < m_drive_motors.size(); i++) {
      m_drive_motors[i] = std::clamp(err * m_p_drive, -127.0f, 127.0f);
      tot_p += m_drive_motors[i].get_position();
      tot_v += m_drive_motors[i].get_target_velocity() -
               m_drive_motors[i].get_actual_velocity();
    }
    err = in - tot_p * .5f * M_PI * m_r_wheel;
    pros::delay(20);
  } while (std::abs(err - tot_p * .25f) <= .2 || tot_v >= 20);
  m_x = std::cos(in - err);
  m_y = std::sin(in - err);
}

void Chassis::driveFor2(const float in) {
  puts("driving forward\n");
  const float distance = in / (2 * M_PI * m_r_wheel);
  for (pros::Motor m : m_drive_motors) {
    m.tare_position();
    m.move_relative(distance, 200);
  };
  float err = distance, position_sum, new_velocity;
  printf("Dist: %.2f\n", distance);
  do {
    pros::delay(20);
    position_sum = 0.0f;
    new_velocity = std::copysignf(
        std::clamp((int)std::abs(err / distance * 200.0f), 70, 200), err);
    for (pros::Motor m : m_drive_motors) {
      m.modify_profiled_velocity(new_velocity);
      position_sum += m.get_position();
    }
    err = distance - (position_sum * 0.25f);
    printf("err: %.2f, adj: %.2f\n", err, new_velocity);
  } while (std::abs(err) > 0.2f);
  const float err_inches = err * 2 * M_PI * m_r_wheel;
  m_x = (in - err_inches) * std::cos(m_θ);
  m_y = (in - err_inches) * std::sin(m_θ);
  puts("done driving forward\n");
}

void Chassis::turnFor(float θ) {
  θ = fmodf(θ, 360.0f);
  if (m_imu == nullptr) return;
  while (m_imu->is_calibrating()) pros::delay(20);
  float err = θ, turnPower;
  m_imu->tare_rotation();
  do {
    pros::delay(20);
    err = θ - (float)m_imu->get_rotation();
    turnPower = std::copysignf(std::clamp(err * m_p_turn, 30.0f, 127.0f), err);
    setSpeeds(turnPower, -turnPower);
  } while (std::abs(err) > 3);
  for (pros::Motor m : m_drive_motors)
    m.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  m_θ += m_imu->get_rotation();
}

void Chassis::splitArcade(int x, int θ) {
  if (useSquareInputs) {
    float temp = x / 127.0f;
    x = 127 * std::copysignf(temp * temp, x);
    temp = θ / 127.0f;
    θ = 127 * std::copysignf(temp * temp, θ);
  }
  int r = std::clamp(x - θ, -127, 127);
  int l = std::clamp(x + θ, -127, 127);
  setSpeeds(l, r);
}

void Chassis::tank(int l, int r) {
  if (useSquareInputs) {
    float temp = l / 127.0f;
    l = 127 * std::copysignf(temp * temp, l);
    temp = r / 127.0f;
    r = 127 * std::copysignf(temp * temp, r);
  }
  setSpeeds(l, r);
}

void Chassis::setSpeeds(int l, int r) {
  m_drive_motors[0] = l;
  m_drive_motors[1] = l;
  m_drive_motors[2] = r;
  m_drive_motors[3] = r;
}
#include "chassis.hpp"
#include "cmath"

Chassis::Chassis(std::vector<pros::Motor> drive_motors, float wheel_radius, float p_drive, float p_turn, pros::Imu *imu)
    : m_drive_motors{drive_motors}, m_r_wheel{wheel_radius}, m_imu{imu}, m_p_drive{p_drive}, m_p_turn{p_turn}
{
    for (int i = 0; i < m_drive_motors.size(); i++)
        m_drive_motors[i].set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
}

void Chassis::setPosition(float x, float y, float θ)
{
    m_x = x;
    m_y = y;
    m_θ = θ;
}

void Chassis::driveTo(float x, float y, bool backwards, float offset)
{
    turnTo(x, y);
    driveFor(std::sqrt(x * x + y * y) - offset);
}

void Chassis::turnTo(float x, float y)
{
    turnFor(m_θ - std::atan2(y - m_y, x - m_x));
}

void Chassis::driveFor(float in)
{
    float err = in, tot_p, tot_v;
    for (int i = 0; i < m_drive_motors.size(); i++)
        m_drive_motors[i].set_zero_position(0);
    do
    {
        tot_p = tot_v = 0.0f;
        for (int i = 0; i < m_drive_motors.size(); i++)
        {
            m_drive_motors[i] = std::clamp(err * m_p_drive, -127.0f, 127.0f);
            tot_p += m_drive_motors[i].get_position();
            tot_v += m_drive_motors[i].get_target_velocity() - m_drive_motors[i].get_actual_velocity();
        }
        err = in - tot_p * .5f * M_PI * m_r_wheel;
        pros::delay(20);
    } while (std::abs(err - tot_p * .25f) <= .2 || tot_v >= 20);
    m_x = std::cos(in - err);
    m_y = std::sin(in - err);
    // for (pros::Motor &m : m_drive_motors)
    //     m.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void Chassis::driveFor2(const float in)
{
    const double distance = in / (2 * M_PI * m_r_wheel);
    for (pros::Motor m : m_drive_motors)
        m.move_relative(distance, 200);
    float err = in, position_sum;
    do
    {
        position_sum = 0.0f;
        for (pros::Motor m : m_drive_motors)
        {
            m.modify_profiled_velocity(err / in * 200 + std::copysignf(50, err));
            position_sum += m.get_position();
        }
    } while (std::abs(position_sum / m_drive_motors.size() - distance) < 10);
}

void Chassis::turnFor(float θ)
{
    if (m_imu == nullptr)
        return;
    float err = 0.0f;
    m_imu->set_rotation(m_θ);
    do
    {
        m_θ = m_imu->get_rotation();
        err = (θ - m_θ) * m_p_turn;
        setSpeeds(err, -err);
        pros::delay(20);
    } while (std::abs(err) <= 1);
}

void Chassis::splitArcade(int x, int θ)
{
    if (useSquareInputs)
    {
        float temp = x / 127.0f;
        x = 127 * std::copysignf(temp * temp, x);
        temp = θ / 127.0f;
        θ = 127 * std::copysignf(temp * temp, θ);
    }
    int r = std::clamp(x - θ, -127, 127);
    int l = std::clamp(x + θ, -127, 127);
    setSpeeds(l, r);
}

void Chassis::tank(int l, int r)
{
    if (useSquareInputs)
    {
        float temp = l / 127.0f;
        l = 127 * std::copysignf(temp * temp, l);
        temp = r / 127.0f;
        r = 127 * std::copysignf(temp * temp, r);
    }
    setSpeeds(l, r);
}

void Chassis::setSpeeds(int l, int r)
{
    m_drive_motors[0] = l;
    m_drive_motors[1] = l;
    m_drive_motors[2] = r;
    m_drive_motors[3] = r;
}
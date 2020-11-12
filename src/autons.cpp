#include "autons.hpp"

void drive(int inches, int32_t velocity)
{
    // LF.set_zero_position(LF.get_position());
    // RF.set_zero_position(RF.get_position());
    // LB.set_zero_position(LB.get_position());
    // RB.set_zero_position(RB.get_position());
    // LF.move_velocity(velocity);
    // RF.move_velocity(velocity);
    // LB.move_velocity(velocity);
    // RB.move_velocity(velocity);
}

void deploySequence()
{
    deployed = true;
    // Elevator = -127;
    // LI = -127;
    // RI = -127;
    pros::delay(500);
    // Elevator = 0;
    // LI = 0;
    // RI = 0;
}

void auton1()
{
    deploySequence();
}
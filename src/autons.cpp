#include "autons.h"

void deploySequence()
{
    MElevator.take(500);
    Elevator.move_relative(900 / 2, 100);
    MElevator.give();
}
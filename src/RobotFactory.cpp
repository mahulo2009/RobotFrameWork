#include "RobotFactory.h"

RobotFactory::RobotFactory() 
{
}

RobotBase * RobotFactory::assembly()
{
    RobotBase * robot = buildRobot();

    WheelBase * wheel_left = buildWheel(0);
    robot->attachLeftWheel(wheel_left);       

    WheelBase * wheel_right = buildWheel(1);
    robot->attachRightWheel(wheel_right); 
}
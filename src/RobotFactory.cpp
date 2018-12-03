#include "RobotFactory.h"

RobotFactory::RobotFactory() 
{
}

RobotBase * RobotFactory::assembly()
{
   
    RobotBase * robot = buildRobot();
    
    WheelBase * wheel_left = buildWheel(0);
    robot->addWheel(wheel_left);       

    WheelBase * wheel_right = buildWheel(1);
    robot->addWheel(wheel_right); 

    return robot;
}
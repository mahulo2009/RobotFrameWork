#include "RobotBase.h"

RobotBase::RobotBase() 	:   previous_command_time_(0),
							x_(0),y_(0),theta_(0),
						    vx_(0),vy_(0),vtheta_(0),
							target_velocity_x_(0),target_velocity_theta_(0)

{
}

void RobotBase::addWheel(WheelBase * wheel)
{
	this->wheels_.push_back(wheel);
}


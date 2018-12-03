#include "RobotBase.h"

RobotBase::RobotBase() 	:   x_(0),y_(0),theta_(0),
						    vx_(0),vy_(0),vtheta_(0)

{
}

void RobotBase::addWheel(WheelBase * wheel)
{
	this->wheels_.push_back(wheel);
}


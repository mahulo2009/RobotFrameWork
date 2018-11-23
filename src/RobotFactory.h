#ifndef Robot_Factory_H
#define Robot_Factory_H

#include "RobotBase.h"
#include <RosConfigBase.h>
#include "WheelBase.h"


class RobotFactory {

  	public:

        RobotFactory();

        virtual RobotBase * assembly();

        virtual RobotBase * buildRobot() = 0;

        virtual WheelBase * buildWheel(int index) = 0;

	protected:

            

  	private:
};
#endif

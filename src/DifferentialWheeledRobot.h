#ifndef Differential_Wheeled_Robot_H
#define Differential_Wheeled_Robot_H

//#define DIFFERENTIAL_WHEELED_ROBOT_DEBUG 1

#include "Arduino.h"
#include "RobotBase.h"

class DifferentialWheeledRobot : public RobotBase {

  	public:
	  
	    DifferentialWheeledRobot(double wheel_separation,double wheel_radious);

		virtual void move(double velocity_x, double velocity_theta);
		virtual void stop();
        virtual void update(double dt);
					
	protected:

	    double wheel_separation_;
	    double wheel_radious_;	

};
#endif

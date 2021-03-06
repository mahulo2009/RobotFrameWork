#ifndef Robot_Base_H
#define Robot_Base_H

#include <WheelBase.h>
#include <vector>

#define COMMAND_TIMEOUT 1500

class RobotBase {

  	public:

        RobotBase();

        virtual void move(double velocity_x, double velocity_theta) = 0;
        virtual void stop() = 0;
        virtual void update(double dt) = 0;
	
		void addWheel(WheelBase * wheel);	
		
        double getX() {return x_;};		
		double getY() {return y_;};
		double getTheta() {return theta_;};				
		double getVx() {return vx_;};
		double getVy() {return vy_;};
		double getVtheta() {return vtheta_;};

		WheelBase * getWheel(unsigned int index) 
		{
			if ( index < 1 || index > wheels_.size() )
			{
				return 0L;
			}
			return wheels_[index]; 
		}

		std::vector<WheelBase * > getWheels() 
		{
			return wheels_;
		}

      
	protected:

		unsigned long previous_command_time_;
    	double x_;
		double y_;
 		double theta_;
		double vx_;
		double vy_;
  		double vtheta_;

		std::vector<WheelBase * > wheels_;

		double target_velocity_x_;
		double target_velocity_theta_;


  	private:

};
#endif

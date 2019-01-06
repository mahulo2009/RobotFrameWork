#ifndef Robot_Base_H
#define Robot_Base_H

#include <WheelBase.h>
#include <vector>

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

		WheelBase * getWheel(int index) 
		{
			return wheels_[index]; //TODO CHECK THE INDEx
		}
      
	protected:

    	double x_;
		double y_;
 		double theta_;
		double vx_;
		double vy_;
  		double vtheta_;

		std::vector<WheelBase * > wheels_;

  	private:

};
#endif

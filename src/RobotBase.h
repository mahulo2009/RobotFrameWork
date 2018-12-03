#ifndef Robot_Base_H
#define Robot_Base_H

#include <WheelBase.h>
#include <vector>

class RobotBase {

  	public:

        RobotBase();

        virtual void move(float velocity_x, float velocity_theta) = 0;
        virtual void stop() = 0;
        virtual void update(float dt) = 0;

		void addWheel(WheelBase * wheel);	
		
        float getX() {return x_;};		
		float getY() {return y_;};
		float getTheta() {return theta_;};				
		float getVx() {return vx_;};
		float getVy() {return vy_;};
		float getVtheta() {return vtheta_;};
      
	protected:

    	float x_;
		float y_;
 		float theta_;
		float vx_;
		float vy_;
  		float vtheta_;

		std::vector<WheelBase * > wheels_;

  	private:

};
#endif
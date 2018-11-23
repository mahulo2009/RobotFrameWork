#ifndef Ros_Config_Base_H
#define Ros_Config_Base_H

#include <ros.h>

class RosConfigBase {

  	public:

            RosConfigBase();

            virtual void read(ros::NodeHandle &nh) = 0;

	protected:

  	private:
          
};
#endif
#ifndef Ros_Config_Sonar_H
#define Ros_Config_Sonar_H

#include <RosConfigBase.h>

class RosConfigSonar : public RosConfigBase {

  	public:

            RosConfigSonar();

            virtual void read(ros::NodeHandle &nh);

            int pin_sonar_trigger;
            int pin_sonar_echo;
            int pin_servo;

	protected:

  	private:
                
};
#endif
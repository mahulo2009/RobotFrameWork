#include "RosConfigSonar.h"

RosConfigSonar::RosConfigSonar()
{
}

void RosConfigSonar::read(ros::NodeHandle &nh)
{
    nh.getParam("/robomat/pin_sonar_trigger", &this->pin_sonar_trigger);
    nh.getParam("/robomat/pin_sonar_echo", &this->pin_sonar_echo);
    nh.getParam("/robomat/pin_servo", &this->pin_servo) ;
}
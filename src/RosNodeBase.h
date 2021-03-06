#ifndef Ros_Node_Base_H
#define Ros_Node_Base_H

#include <ros.h>
#include <tf/transform_broadcaster.h>

class RosNodeBase {

  	public:

            RosNodeBase();

            virtual void init(ros::NodeHandle &nh) = 0;                       
            virtual void update(ros::Time &current_time) = 0;
};
#endif
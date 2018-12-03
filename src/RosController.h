#ifndef Ros_Controller_H
#define Ros_Controller_H


#include <RosNodeBase.h>
#include <ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <sensor_msgs/Range.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <vector>

#include <RosConfigBase.h>

#define ROS_CONTROLLER_DEBUG 1

typedef  RosNodeBase * RosNodeBasePtr;

class RosController {

  	public:

            RosController();

            RosController(IPAddress * server, uint16_t server_port); //TODO RECOVER THIS

            void init();
            void readConfiguration(RosConfigBase * ros_config);
            void update();
            
            inline void addNode(RosNodeBasePtr ros_node ) 
            {
                  ros_nodes.push_back(ros_node);
            }
                    
	protected:

            ros::NodeHandle nh;                     
            tf::TransformBroadcaster broadcaster;   

            ros::Time current_time_;
            ros::Time last_time_;

  	private:

            void init_();

            std::vector<RosNodeBasePtr> ros_nodes;
            
};
#endif
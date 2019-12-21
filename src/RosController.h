#ifndef Ros_Controller_H
#define Ros_Controller_H

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h> // Using Espressif's WiFi.h
#else
  #include <SPI.h>
  #include <Ethernet.h>
#endif

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

//#define ROS_CONTROLLER_DEBUG 1

typedef  RosNodeBase * RosNodeBasePtr;

class RosController {

  	public:

            RosController();
            
            #if defined(ESP8266)
            RosController(IPAddress * server, uint16_t server_port);
            #endif

            void init();
            void readConfiguration(RosConfigBase * ros_config);
            void update();
            
            inline void addNode(RosNodeBasePtr ros_node) 
            {
                  ros_nodes.push_back(ros_node);
            }
                    
	protected:

            ros::NodeHandle nh;                     

  	private:

            void init_();

            std::vector<RosNodeBasePtr> ros_nodes;
            
};
#endif

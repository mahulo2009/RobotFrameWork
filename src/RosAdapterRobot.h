#ifndef Ros_Robot_Adapter_H
#define Ros_Robot_Adapter_H

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include "robotin_project/RAW_VEL.h"
#include "robotin_project/PID.h"

#include <RosNodeBase.h>
#include <RobotBase.h>

class RosAdapterRobot  : public RosNodeBase {

  	public:

        RosAdapterRobot();

        virtual void init(ros::NodeHandle &nh);
        virtual void update(ros::Time &current_time);
        
        void cmd_velocity_callback(const geometry_msgs::Twist& CVel);
        void pid_callback(const robotin_project::PID& pid);

        void attachRobot(RobotBase * robot);
                                
	protected:

  	private:
            
        ros::Subscriber<geometry_msgs::Twist, RosAdapterRobot> cmd_velocity_sub_;
        ros::Subscriber<robotin_project::PID, RosAdapterRobot> cmd_pid_sub_;

        robotin_project::RAW_VEL raw_vel_msg_;
        ros::Publisher raw_vel_pub_;            
        
        RobotBase * robot_; 
};
#endif

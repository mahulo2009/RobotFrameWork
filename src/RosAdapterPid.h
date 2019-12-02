#ifndef Ros_Adapter_Pid_H
#define Ros_Adapter_Pid_H

#include <ros.h>

#include <RosNodeBase.h>
#include <RobotBase.h>
#include "robotin_project/PID.h" //TODO

class RosAdapterPid : public RosNodeBase {

  	public:

        RosAdapterPid();
        
        virtual void init(ros::NodeHandle &nh);
        virtual void update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster);

        void pid_callback(const robotin_project::PID& pid);
        void attachRobot(RobotBase * robot);
                    
	protected:

  	private:

        ros::Subscriber<robotin_project::PID, RosAdapterPid> pid_sub_;
        robotin_project::PID pid_msg_;            

        /*               
        geometry_msgs::TransformStamped pid_trans_;                                       
        ros::Publisher pid_pub_;
        */

        RobotBase * robot_; 
};
#endif
/*

            ros::Subscriber<geometry_msgs::Twist, RosAdapterRobot> cmd_velocity_sub_;            
            ros::Publisher odom_pub_;
            nav_msgs::Odometry odom_nav_msg_;
            geometry_msgs::TransformStamped odom_trans_; 
            RobotBase * robot_; 
            bool sendTF_;
*/

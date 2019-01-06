#ifndef Ros_Pid_Adapter_H
#define Ros_Pid_Adapter_H

#include <ros.h>

#include "RosNodeBase.h"
#include "WheelEncoder.h"
#include <rosserial_arduino/Test.h>

using rosserial_arduino::Test;

class RosAdapterPid  : public RosNodeBase {

  	public:

        RosAdapterPid();

        virtual void init(ros::NodeHandle &nh);
        virtual void update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster);

        void attachWheel(WheelBase * wheel);

        void callback(const Test::Request & req, Test::Response & res);
                    
	protected:

  	private:

        geometry_msgs::Vector3 pid_telemetry_wheel_msg_;              
        WheelBase * wheel_; 
        ros::Publisher pid_telemetry_wheel_pub_;

        ros::ServiceServer<Test::Request, Test::Response,RosAdapterPid > server;

        ros::NodeHandle *nh_;

};
#endif


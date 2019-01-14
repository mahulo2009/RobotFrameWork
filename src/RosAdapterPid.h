#ifndef Ros_Pid_Adapter_H
#define Ros_Pid_Adapter_H

#include <ros.h>

#include "Pid.h"
#include "RosNodeBase.h"
#include "WheelEncoder.h"
#include <robomat_project/PidTunning.h>

using namespace robomat_project;

class RosAdapterPid  : public RosNodeBase {

  	public:

            RosAdapterPid();

            virtual void init(ros::NodeHandle &nh);
            virtual void update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster);

            void attachWheel(std::vector<WheelBase * > wheels_);

            void callback(const PidTunning::Request & req, PidTunning::Response & res);
                    
	protected:

  	private:

            geometry_msgs::Vector3 pid_telemetry_wheel_msg_;              
            std::vector<WheelBase * > wheels_;
            WheelBase * wheel_;
            ros::Publisher pid_telemetry_wheel_pub_;
            ros::NodeHandle * nh_;
            ros::ServiceServer<PidTunning::Request, PidTunning::Response,RosAdapterPid > server;

            

};
#endif


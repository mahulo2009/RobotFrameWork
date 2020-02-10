#ifndef Ros_Adapter_Pid_H
#define Ros_Adapter_Pid_H

#include <ros.h>

#include <RosNodeBase.h>
#include <WheelBase.h>
#include "robotin_project/PID.h"
#include "robotin_project/VEL.h"
#include "robotin_project/TEL.h"

class RosAdapterPid : public RosNodeBase
{

public:
        RosAdapterPid(String cmd_vel, String cmp_pid, String tel_vel);

        virtual void init(ros::NodeHandle &nh);
        virtual void update(ros::Time &current_time);

        void pid_callback(const robotin_project::PID &pid);
        void vel_callback(const robotin_project::VEL &vel);
        void attachWheel(WheelBase *wheel);

protected:
private:
        ros::Subscriber<robotin_project::VEL, RosAdapterPid> cmd_vel_sub_;
        ros::Subscriber<robotin_project::PID, RosAdapterPid> cmd_pid_sub_;
        ros::Publisher tel_pub_;

        robotin_project::TEL tel_msg_;
        WheelBase *wheel_;
        String cmd_vel_;
        String cmd_pid_;
        String tel_vel_;
};
#endif
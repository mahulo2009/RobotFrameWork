#include "RosAdapterPid.h"
#include <Pid.h>
#include <WheelEncoder.h>

RosAdapterPid::RosAdapterPid(String cmd_vel, String cmd_pid,String tel_vel): 
    cmd_vel_(cmd_vel),  
    cmd_pid_(cmd_pid),
    tel_vel_(tel_vel),
    cmd_vel_sub_(cmd_vel_.c_str(), 
        &RosAdapterPid::vel_callback,
        this), 
    cmd_pid_sub_(cmd_pid_.c_str(), 
        &RosAdapterPid::pid_callback,
        this), 
    tel_pub_(tel_vel_.c_str(), &tel_msg_),
    wheel_(0)
{
    cmd_vel_sub_.topic_=cmd_vel_.c_str();
    cmd_pid_sub_.topic_=cmd_pid_.c_str();
    tel_pub_.topic_=tel_vel_.c_str();
}

void RosAdapterPid::attachWheel(WheelBase * wheel)
{
    this->wheel_ = wheel;
}


void RosAdapterPid::pid_callback(const robotin_project::PID& pid_params)
{
    if ( wheel_ != 0 ) 
    {
        WheelEncoder *w = (WheelEncoder *)(wheel_);
        Pid * pid = w->getPid();

        pid->reset();
        pid->setKp(pid_params.p);
        pid->setKi(pid_params.i);
        pid->setKd(pid_params.d);
    }
    
}

void RosAdapterPid::vel_callback(const robotin_project::VEL& vel_params)
{    
    if ( wheel_ != 0 ) 
    {
        wheel_->move(vel_params.velocity);
    }    
}

void RosAdapterPid::init(ros::NodeHandle &nh)
{
    nh.advertise(tel_pub_);
    nh.subscribe(cmd_pid_sub_);
    nh.subscribe(cmd_vel_sub_);
}
   
void RosAdapterPid::update(ros::Time &current_time)
{   
    if (wheel_ != 0 )  
    {
        tel_msg_.current_velocity=wheel_->getVelocity();
        tel_msg_.demanded_velocity=wheel_->getDemandedVelocity();
        tel_msg_.target_velocity=wheel_->getTargetVelocity();
    
        tel_pub_.publish(&tel_msg_);
    }
}

#include "RosAdapterPid.h"

RosAdapterPid::RosAdapterPid() : 
    wheel_(0) ,
    pid_telemetry_wheel_pub_("/car/pid_telemetry_wheel_msg", &pid_telemetry_wheel_msg_),
    server("test_srv",&RosAdapterPid::callback,this)
{   
}

void RosAdapterPid::init(ros::NodeHandle &nh)
{
    nh.advertise(pid_telemetry_wheel_pub_);
    nh.advertiseService(server);

    this->nh_ = &nh;
}
void RosAdapterPid::attachWheel(WheelBase * wheel) 
{
    this->wheel_ = wheel;
}

void RosAdapterPid::callback(const Test::Request & req, Test::Response & res)
{
    res.output = "hello";

    WheelEncoder * wheel_encoder = (WheelEncoder *)(wheel_);

    Pid * pid = wheel_encoder->getPid();


    //TODO RATHER THAN GETTING THIS FROM PARAMS; CREATE A MESSAGE TO SEND THIS VALUES USING ACTIONLIB
    float pid_kp, pid_ki, pid_kd, pid_velocity;
    nh_->getParam("/robomat/pid_kp", &pid_kp);
    nh_->getParam("/robomat/pid_ki", &pid_ki);
    nh_->getParam("/robomat/pid_kd", &pid_kd);
    nh_->getParam("/robomat/pid_velocity", &pid_velocity);

    pid->reset();
    pid->setKp(pid_kp);
    pid->setKi(pid_ki);
    pid->setKd(pid_kd);

    wheel_->stop();
    wheel_->move(pid_velocity);
}

void RosAdapterPid::update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster)
{
    if ( wheel_ != 0 ) 
    {
        pid_telemetry_wheel_msg_.x=wheel_->getTargetVelocity();
        pid_telemetry_wheel_msg_.y=wheel_->getVelocity();
        pid_telemetry_wheel_msg_.z=wheel_->getDemandedVelocity();
        pid_telemetry_wheel_pub_.publish(&pid_telemetry_wheel_msg_);   
    }
}
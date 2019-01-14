#include "RosAdapterPid.h"

RosAdapterPid::RosAdapterPid() : 
    pid_telemetry_wheel_pub_("/car/pid_telemetry_wheel_msg", &pid_telemetry_wheel_msg_),
    server("test_srv",&RosAdapterPid::callback,this),
    wheel_(0)
{   
}

void RosAdapterPid::init(ros::NodeHandle &nh)
{
    nh.advertise(pid_telemetry_wheel_pub_);
    nh.advertiseService(server); 

    this->nh_ = &nh;
}

void RosAdapterPid::attachWheel(std::vector<WheelBase * > wheels) 
{
    this->wheels_ = wheels;
}

void RosAdapterPid::callback(const PidTunning::Request & req, PidTunning::Response & res)
{
    wheel_ = wheels_[req.wheel];

    wheel_->stop();
    
    
    delay(1000);
    

    WheelEncoder * wheel_encoder = (WheelEncoder *)(wheel_);
    Pid * pid = wheel_encoder->getPid();

    pid->reset();
    pid->setKp(req.kp);
    pid->setKi(req.ki);
    pid->setKd(req.kd);
    
    wheel_->move(req.vel);

    res.rise_time = -1;
    res.percent_overshoot = 0;
    res.settling_time = 0;
    res.steady_state_error = 0;

    for(int i=1;i<=80;i++) 
    {

        nh_->loginfo((String(wheel_->getVelocity()) + " " + String(wheel_->getTargetVelocity())).c_str());
        nh_->spinOnce();
        
        delay(250);
        
        wheel_->update(0.250);

        if ( ( wheel_->getVelocity() >= wheel_->getTargetVelocity() ) && res.rise_time == -1 ) {
            res.rise_time = 100*i;
        }

        if ( ( wheel_->getVelocity() >= wheel_->getTargetVelocity() ) ) {
            res.percent_overshoot++;
        }      

        if ( ( wheel_->getVelocity() <= wheel_->getTargetVelocity() + 1.0 ) && 
             ( wheel_->getVelocity() >= wheel_->getTargetVelocity() - 1.0 ) && 
             res.settling_time == -1) 
        {
            res.settling_time = 100*i;   
        }
        else if ( ( wheel_->getVelocity() >= wheel_->getTargetVelocity() + 1.0 ) || 
                  ( wheel_->getVelocity() <= wheel_->getTargetVelocity() - 1.0 ) )
        {
            res.settling_time = -1;   
        }

        
    }

    res.percent_overshoot = ((res.percent_overshoot*100)/20000.0)*100;

    wheel_->stop();
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
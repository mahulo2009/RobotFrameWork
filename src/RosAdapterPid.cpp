#include "RosAdapterPid.h"
#include <Pid.h>
#include <WheelEncoder.h>


RosAdapterPid::RosAdapterPid() : 
    pid_sub_("/car/pid", 
        &RosAdapterPid::pid_callback,
        this),    
    //pid_pub_("pid", &pid_msg_),
    robot_(0)
{
}

void RosAdapterPid::attachRobot(RobotBase * robot) 
{
    this->robot_ = robot;
}

void RosAdapterPid::pid_callback(const robotin_project::PID& pid_params)
{
    if ( robot_ != 0 ) 
    {
        std::vector<WheelBase * > wheels = robot_->getWheels();
        for (int i=0;i<wheels.size();i++) 
        {
            WheelEncoder *w = (WheelEncoder *)(wheels[0]);
            Pid * pid = w->getPid();

            pid->reset();
            pid->setKp(pid_params.p);
            pid->setKi(pid_params.i);
            pid->setKd(pid_params.d);
        }
    }
}

void RosAdapterPid::init(ros::NodeHandle &nh)
{
    
    //nh.advertise(pid_pub_);  
}
   
void RosAdapterPid::update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster)
{   
    /*
    if (wheel_ != 0 )  
    {
        Serial.println("RosAdapterPid::update");

        imu_msg_.linear_acceleration = imu_->readAccelerometer();
        imu_msg_.angular_velocity = imu_->readGyroscope();
        imu_msg_.magnetic_field = imu_->readMagnetometer();
    
        imu_pub_.publish(&imu_msg_);

    }
    */
}

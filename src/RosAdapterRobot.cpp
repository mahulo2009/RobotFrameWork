#include "RosAdapterRobot.h"
#include "WheelEncoder.h"
#include "Pid.h"

RosAdapterRobot::RosAdapterRobot() : 
    cmd_velocity_sub_("/car/cmd_vel", 
                        &RosAdapterRobot::cmd_velocity_callback,
                        this),
    cmd_pid_sub_("/car/cmd_pid", 
                        &RosAdapterRobot::pid_callback,
                        this), 
    raw_vel_pub_("/car/raw_vel", &raw_vel_msg_),
    robot_(0)
{   
}

void RosAdapterRobot::init(ros::NodeHandle &nh)
{
    nh.subscribe(cmd_velocity_sub_);
    nh.subscribe(cmd_pid_sub_);
    nh.advertise(raw_vel_pub_);
}

void RosAdapterRobot::cmd_velocity_callback(const geometry_msgs::Twist& CVel)
{
    if ( robot_ != 0 ) 
    {
        robot_->move(CVel.linear.x,CVel.angular.z);  
    }
}

void RosAdapterRobot::pid_callback(const robotin_project::PID& pid_params)
{
    if ( robot_ != 0 ) 
    {
        std::vector<WheelBase * > wheels = robot_->getWheels();
        for (unsigned int i=0;i<wheels.size();i++) 
        {
            WheelEncoder *w = (WheelEncoder *)(wheels[i]);
            Pid * pid = w->getPid();

            pid->reset();
            pid->setKp(pid_params.p);
            pid->setKi(pid_params.i);
            pid->setKd(pid_params.d);
            
        }
    }
}

void RosAdapterRobot::attachRobot(RobotBase * robot) 
{
    this->robot_ = robot;
}

void RosAdapterRobot::update(ros::Time &current_time)
{
    if (robot_ != 0 )  
    {
        raw_vel_msg_.linear_x=robot_->getVx();
        raw_vel_msg_.linear_y=robot_->getVy();
        raw_vel_msg_.angular_z=robot_->getVtheta();
    
        raw_vel_pub_.publish(&raw_vel_msg_);
    }
}

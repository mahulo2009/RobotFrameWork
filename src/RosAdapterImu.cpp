#include "RosAdapterImu.h"

RosAdapterImu::RosAdapterImu() :     
    imu_pub_("raw_imu", &imu_msg_),
    imu_(0)
{
}

void RosAdapterImu::init(ros::NodeHandle &nh)
{
    nh.advertise(imu_pub_);  
}
   
void RosAdapterImu::update(ros::Time &current_time)
{   
    if (imu_ != 0 )  
    {
        Serial.println("RosAdapterImu::update");

        imu_msg_.linear_acceleration = imu_->readAccelerometer();
        imu_msg_.angular_velocity = imu_->readGyroscope();
        imu_msg_.magnetic_field = imu_->readMagnetometer();

        imu_pub_.publish(&imu_msg_);
    }
}

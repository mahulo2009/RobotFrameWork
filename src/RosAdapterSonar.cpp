#include "RosAdapterSonar.h"

RosAdapterSonar::RosAdapterSonar() : 
    sonar_pose_sub_("/car/sonar_pose", &RosAdapterSonar::sonar_pose_callback ,this),
    ultrasonic_pub_("/car/ultrasound", &ultrasonic_msg_),
    sonar_(0)
{
}

void RosAdapterSonar::init(ros::NodeHandle &nh)
{
    nh.subscribe(sonar_pose_sub_);
    nh.advertise(ultrasonic_pub_);
  
    ultrasonic_msg_.radiation_type = sensor_msgs::Range::ULTRASOUND;
    ultrasonic_msg_.header.frame_id = "/ultrasound";   
    ultrasonic_msg_.field_of_view = 0.1;
    ultrasonic_msg_.min_range = 0.0;
    ultrasonic_msg_.max_range = 20;
}

void RosAdapterSonar::sonar_pose_callback( const geometry_msgs::Pose2D & sonar_pose) 
{
    if (sonar_ != 0 ) { 
        sonar_->moveTo(sonar_pose.theta);
    }
}
   
void RosAdapterSonar::update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster)
{   
    if (sonar_ != 0 )  
    {
    
        ultrasonic_trans_.header.frame_id = "/base_link";
        ultrasonic_trans_.child_frame_id = "/ultrasound";
        ultrasonic_trans_.transform.translation.x = 0.045; 
        ultrasonic_trans_.transform.translation.y = 0.0; 
        ultrasonic_trans_.transform.translation.z = 0.075;
        ultrasonic_trans_.transform.rotation = tf::createQuaternionFromYaw(sonar_->getAngle()); //TODO INCLUDE ORIENTATION + RELATIVE POSITION SENSOR.
        ultrasonic_trans_.header.stamp = current_time;
        broadcaster.sendTransform(ultrasonic_trans_);

        ultrasonic_msg_.range = sonar_->read()/100.0; //TODO IMPROVE THIS UNITS
        ultrasonic_msg_.header.stamp = current_time;
        ultrasonic_pub_.publish(&ultrasonic_msg_);    

    }
}
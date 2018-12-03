#ifndef Ros_Adapter_Sonar_H
#define Ros_Adapter_Sonar_H

#include <ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/Range.h>
#include <geometry_msgs/Pose2D.h>

#include <RosNodeBase.h>
#include <Sonar.h>

//TODO MOVE TO FRAMEWORK

class RosAdapterSonar : public RosNodeBase {

  	public:

            RosAdapterSonar();
            
            virtual void init(ros::NodeHandle &nh);
            virtual void update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster);
            
            
            void sonar_pose_callback( const geometry_msgs::Pose2D & sonar_pose);

            void attachSonar(Sonar * sonar) {
                this->sonar_=sonar;
            }
                    
	protected:

  	private:

            ros::Subscriber<geometry_msgs::Pose2D, RosAdapterSonar> sonar_pose_sub_;
            geometry_msgs::TransformStamped ultrasonic_trans_;                                       
            ros::Publisher ultrasonic_pub_;
            sensor_msgs::Range ultrasonic_msg_;            

            Sonar * sonar_;
};
#endif
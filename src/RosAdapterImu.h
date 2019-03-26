#ifndef Ros_Adapter_Imu_H
#define Ros_Adapter_Imu_H

#include <ros.h>

#include <RosNodeBase.h>
#include <ImuBase.h>
#include "gara_project/Imu.h" //TODO

class RosAdapterImu : public RosNodeBase {

  	public:

            RosAdapterImu();
            
            virtual void init(ros::NodeHandle &nh);
            virtual void update(ros::Time &current_time,tf::TransformBroadcaster &broadcaster);

            void attachImu(ImuBase * imu) {
                this->imu_ = imu;
            }
                    
	protected:

  	private:
            
            geometry_msgs::TransformStamped imu_trans_;                                       
            ros::Publisher imu_pub_;
            gara_project::Imu imu_msg_;            

            ImuBase * imu_;
};
#endif

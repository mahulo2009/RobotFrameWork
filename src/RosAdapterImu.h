#ifndef Ros_Adapter_Imu_H
#define Ros_Adapter_Imu_H

#include <ros.h>

#include <RosNodeBase.h>
#include <ImuBase.h>
#include <lino_msgs/Imu.h>

class RosAdapterImu : public RosNodeBase {

  	public:

            RosAdapterImu();
            
            virtual void init(ros::NodeHandle &nh);
            virtual void update(ros::Time &current_time);

            void attachImu(ImuBase * imu) {
                this->imu_ = imu;
            }
                    
	protected:

  	private:
            
            geometry_msgs::TransformStamped imu_trans_;                                       
            ros::Publisher imu_pub_;
            lino_msgs::Imu imu_msg_;            

            ImuBase * imu_;
};
#endif

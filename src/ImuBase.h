#ifndef ImuBase_H
#define ImuBase_H

#include "Arduino.h"
#include "geometry_msgs/Vector3.h"

#define IMU_DEBUG 1

struct axis_3 
{
    int16_t x, y, z;
};

class ImuBase {

    public:

	    ImuBase();			
	
        virtual geometry_msgs::Vector3 readAccelerometer() = 0;
        virtual geometry_msgs::Vector3 readGyroscope() = 0;
        virtual geometry_msgs::Vector3 readMagnetometer() = 0;
	
    private:

};
#endif
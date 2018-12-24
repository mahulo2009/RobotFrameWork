#ifndef WheelBase_H
#define WheelBase_H

#include "HardwareController.h"

//#define WHEEL_DEBUG 1

class WheelBase {

    public:

        WheelBase();														    //default constructor.

        void attachController(HardwareController * controller);   
        virtual void move(float velocity) = 0;
        virtual void stop() = 0;

        inline float getTargetVelocity() 
            {return targetVelocity_;};
        inline float getVelocity() 
            {return currentVelocity_;};
        inline float getDemandedVelocity() 
            {return demandedVelocity_;};

        inline float getDistance() 
            {return distance_;};

        inline void setDistance(float distance) 
            {this->distance_=distance;};

        HardwareController * getHardwareController() {
            return controller_;
        }
        
        virtual void update() = 0;

        float distance_;
        
    protected:

        float targetVelocity_;      //Target velocity [radians per second] 
		float currentVelocity_;			//Current velocity [radians per second] 
        float demandedVelocity_;    //Demanded velocity [radians per second]  

        HardwareController * controller_;

};
#endif


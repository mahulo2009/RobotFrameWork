#ifndef WheelBase_H
#define WheelBase_H

#include "HardwareController.h"

//#define WHEEL_DEBUG 1

class WheelBase {

    public:

        WheelBase();														    //default constructor.

        void attachController(HardwareController * controller);   
        virtual void move(double velocity) = 0;
        virtual void stop() = 0;
        virtual void update(double dt) = 0;

        inline double getTargetVelocity() 
            {return targetVelocity_;};
        inline double getVelocity() 
            {return currentVelocity_;};
        inline double getDemandedVelocity() 
            {return demandedVelocity_;};

        inline double getDistance() 
            {return distance_;};

        inline void setDistance(double distance) 
            {this->distance_=distance;};

        HardwareController * getHardwareController() {
            return controller_;
        }
        
        

        float distance_;
        
    protected:

        double targetVelocity_;      //Target velocity [radians per second] 
		double currentVelocity_;			//Current velocity [radians per second] 
        double demandedVelocity_;    //Demanded velocity [radians per second]  

        HardwareController * controller_;

};
#endif


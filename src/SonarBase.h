#ifndef SonarBase_H
#define SonarBase_H

//#include "HardwareController.h"

//#define SONAR_DEBUG 1

class SonarBase {

    public:

        SonarBase();														    //default constructor.

        virtual void moveTo(float angle) = 0;

        virtual unsigned int read() = 0;

        virtual float getAngle() = 0;
        
    protected:

};
#endif
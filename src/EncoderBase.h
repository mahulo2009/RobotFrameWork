#ifndef EncoderBase_H
#define EncoderBase_H

//#define ENCODER_DEBUG 1

class EncoderBase {

    public:

	    EncoderBase();			
	
        virtual void setupDirection(int direction) = 0;			
	    virtual double getVelocity(double dt) = 0;				
	
    private:

};
#endif

#ifndef EncoderBase_H
#define EncoderBase_H

//#define ENCODER_DEBUG 1

class EncoderBase {

    public:

	    EncoderBase();			
	
        virtual void setupDirection(int direction) = 0;			
	    virtual float getVelocity(float dt) = 0;				
	
    private:

};
#endif

#include "DifferentialWheeledRobot.h"

DifferentialWheeledRobot::DifferentialWheeledRobot(double wheel_separation, double wheel_radious): 
															wheel_separation_(wheel_separation),wheel_radious_(wheel_radious)
{

}

void DifferentialWheeledRobot::move(double velocity_x, double velocity_theta)
{
  double velocity_1  = ( 2 * velocity_x + velocity_theta * wheel_separation_) / ( 2 * wheel_radious_ );
  double velocity_2  = ( 2 * velocity_x - velocity_theta * wheel_separation_) / ( 2 * wheel_radious_ );

  wheels_[0]->move(velocity_1);
  wheels_[1]->move(velocity_2);

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
  Serial.print("DifferentialWheeledRobot::move:");
  Serial.print("\t");
  Serial.print(velocity_1);
  Serial.print("\t");
  Serial.print(velocity_2);
  Serial.print("\n");
	#endif
}

void DifferentialWheeledRobot::stop()
{
	wheels_[0]->stop();
	wheels_[1]->stop();
}


void DifferentialWheeledRobot::update(double dt)
{

  float velocity_1 =  wheels_[0]->getVelocity();  
  float velocity_2 =  wheels_[1]->getVelocity();

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
	Serial.print("DifferentialWheeledRobot::update:");
  Serial.print("\t");
  Serial.print(velocity_1);
  Serial.print("\t");
  Serial.print(velocity_2);
  Serial.print("\n");
	#endif

	vx_     = ( wheel_radious_ * ( velocity_1 + velocity_2 ) ) / 2.;
	vy_     = 0;
  vtheta_ = ( ( wheel_radious_ * ( velocity_1 - velocity_2 ) ) /  ( wheel_separation_ ) ) ;

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
	Serial.print("DifferentialWheeledrRobot::update:");
  Serial.print("\t");
  Serial.print(vx_);
  Serial.print("\t");
  Serial.print(vtheta_);
  Serial.print("\n");
	#endif
  
  theta_  += vtheta_ * dt;
	x_      +=  vx_ * cos(theta_) * dt;
	y_      +=  vx_ * sin(theta_) * dt;

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
	Serial.print("DifferentialWheeledRobot::update:");
  Serial.print("\t");
  Serial.print(x_);
  Serial.print("\t");
  Serial.print(y_);
  Serial.print("\t");
  Serial.print(theta_);
  Serial.print("\n");
	#endif
}
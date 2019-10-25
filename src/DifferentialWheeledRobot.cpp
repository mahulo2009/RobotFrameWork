#include "DifferentialWheeledRobot.h"

DifferentialWheeledRobot::DifferentialWheeledRobot(double wheel_separation, double wheel_radious): 
															wheel_separation_(wheel_separation),wheel_radious_(wheel_radious)
{

}

void DifferentialWheeledRobot::move(double velocity_x, double velocity_theta)
{
  target_velocity_x_ = velocity_x;
  target_velocity_theta_ = velocity_theta;
}

void DifferentialWheeledRobot::stop()
{
	wheels_[0]->stop();
	wheels_[1]->stop();
}


void DifferentialWheeledRobot::update(double dt)
{
  
  double velocity_1  = 0;
  double velocity_2  = 0;

  if ((millis() - previous_command_time_) <= COMMAND_TIMEOUT)
  {
    velocity_1  = ( 2 * target_velocity_x_ + target_velocity_theta_ * wheel_separation_) / ( 2 * wheel_radious_ );
    velocity_2  = ( 2 * target_velocity_x_ - target_velocity_theta_ * wheel_separation_) / ( 2 * wheel_radious_ );
  }

  if (wheels_.size() == 2) 
  {
    if (wheels_[0] != 0)
      wheels_[0]->move(velocity_1);
    if (wheels_[1] != 0)      
      wheels_[1]->move(velocity_2);
  }

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
  Serial.print("DifferentialWheeledRobot::move:");
  Serial.print(" velocity1\t");
  Serial.print(velocity_1);
  Serial.print(" velocity2\t");
  Serial.print(velocity_2);
  Serial.print("\n");
	#endif

  previous_command_time_ = millis();
    
  if (wheels_.size() == 2) 
  {
    if (wheels_[0] != 0)
      velocity_1 =  wheels_[0]->getVelocity();  
    if (wheels_[1] != 0)
      velocity_2 =  wheels_[1]->getVelocity();
  }

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
	Serial.print("DifferentialWheeledRobot::update:");
  Serial.print(" velocity1\t");
  Serial.print(velocity_1);
  Serial.print(" velocity2\t");
  Serial.print(velocity_2);
  Serial.print("\n");
	#endif

	vx_     = ( wheel_radious_ * ( velocity_1 + velocity_2 ) ) / 2.;
	vy_     = 0;
  vtheta_ = ( ( wheel_radious_ * ( velocity_1 - velocity_2 ) ) /  ( wheel_separation_ ) ) ;

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
	Serial.print("DifferentialWheeledRobot::update:");
  Serial.print(" vx\t");
  Serial.print(vx_);
  Serial.print(" vtheta\t");
  Serial.print(vtheta_);
  Serial.print("\n");
	#endif
  
  theta_  += vtheta_ * dt;
	x_      +=  vx_ * cos(theta_) * dt;
	y_      +=  vx_ * sin(theta_) * dt;

	#ifdef DIFFERENTIAL_WHEELED_ROBOT_DEBUG
	Serial.print("DifferentialWheeledRobot::update:");
  Serial.print(" x\t");
  Serial.print(x_);
  Serial.print(" y\t");
  Serial.print(y_);
  Serial.print(" theta\t");
  Serial.print(theta_);
  Serial.print("\n");
	#endif
}
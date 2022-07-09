/***********************************************************************
 * Header File:
 *    Velocity : Represents a 2-dimensional velocity in the
 *    orbit simulation
 * Author:
 *    Emilio Regino & Bradley Payne
 * Summary:
 *    Tracks the components of a 2-dimensional velocity, and provides
 *    a simple way to apply an acceleration over time.
 ************************************************************************/

#include "velocity.h"      // for the VELOCITY class


/***********************************************************************
 * VELOCITY ACCELERATION CONSTRUCTOR
 * A constructor to set this velocity from an initial velocity and
 * acceleration given as arguements over a specified amount of
 * time.
 ************************************************************************/
Velocity::Velocity(Velocity initVelocity, Acceleration accel, double time)
{
   velocityX = initVelocity.getX();
   velocityY = initVelocity.getY();
   this->applyAcceleration(accel, time);
}

/***********************************************************************
 * VELOCITY ANGLE MAGNITUDE CONSTRUCTOR
 * A constructor to set this velocity from an angle and magnitude
 ************************************************************************/
Velocity::Velocity(Angle angle, double magnitude)
{
   // Calculate and set the horizontal and vertical components
   setX(magnitude * sin(angle.getRadian()));
   setY(magnitude * cos(angle.getRadian()));
}

/***********************************************************************
 * GET SPEED
 * A method to get the total magnitude of the velocity.
 ************************************************************************/
double Velocity::getSpeed() const
{
   return sqrt(velocityX * velocityX + velocityY * velocityY);
}

/***********************************************************************
 * APPLY ACCELERATION
 * A method to apply acceleration to velocity over a specified
 * amount of time
 ************************************************************************/
void Velocity::applyAcceleration(Acceleration accel, double time)
{
   velocityX += accel.getX() * time;
   velocityY += accel.getY() * time;
}

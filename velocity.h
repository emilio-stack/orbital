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

#pragma once

#include "acceleration.h"  // for the ACCELERATION class
#include <cmath>           // for SQRT function

/***********************************************************************
 * VELOCITY
 * A 2D velocity in the orbit simulator
 ************************************************************************/
class Velocity
{
public:
   // constructors
   Velocity(): velocityX(0.0), velocityY(0.0) {};
   Velocity(double velX, double velY): velocityX(velX), velocityY(velY) {};
   Velocity(Velocity initVelocity, Acceleration accel, double time);
   
   // getters
   virtual double getVelocityX() const { return velocityX; }
   virtual double getVelocityY() const { return velocityY; }
   virtual double getSpeed() const;
   
   // mutators
   virtual void applyAcceleration(Acceleration accel, double time);
   void setDX(double value) { velocityX = value; }
   void setDY(double value) { velocityY = value; }
   
   // operators
   Velocity & operator= (const Velocity & rhs);
   bool operator== (const Velocity& rhs);
   
protected:
   double velocityX;    // The horizontal velocity
   double velocityY;    // The vertical velocity
};

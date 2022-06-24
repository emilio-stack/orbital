/***********************************************************************
 * Header File:
 *    Acceleration : Represents a 2-dimensional acceleration in the
 *    orbit simulation
 * Author:
 *    Emilio Regino
 * Summary:
 *    Tracks the components of a 2-dimensional acceleration, and provides
 *    a simple way to add two accelerations together.
 ************************************************************************/

#pragma once

#include "angle.h"   // for ANGLE class

/***********************************************************************
 * ACCELERATION
 * A 2D acceleration in the orbit simulator
 ************************************************************************/
class Acceleration
{
public:
   // constructors
   Acceleration(): accelX(0.0), accelY(0.0) {};
   Acceleration(double x, double y): accelX(x), accelY(y) {};
   Acceleration(Angle angle, double magnitude);
   
   // getters
   virtual double getX() const { return accelX; }
   virtual double getY() const { return accelY; }
   
   // mutators
   virtual void addAcceleration(Acceleration otherAccel);
   void setX(double value) { accelX = value; }
   void setY(double value) { accelY = value; }
   
protected:
   double accelX;    // the horizontal component of acceleration
   double accelY;    // the vertical component of acceleration
};

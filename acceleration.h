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
   friend class TestAcceleration;
   // constructors
   Acceleration(): x(0.0), y(0.0) {};
   Acceleration(double x, double y): x(x), y(y) {};
   Acceleration(Angle angle, double magnitude);
   
   // getters
   virtual double getX() const { return x; }
   virtual double getY() const { return y; }
   
   // mutators
   virtual void addAcceleration(Acceleration otherAccel);
   void setX(double value) { x = value; }
   void setY(double value) { y = value; }
   
protected:
   double x;    // the horizontal component of acceleration
   double y;    // the vertical component of acceleration
   
private:
   bool closeEnough(double computedValue, double hardcodeValue) const;
};

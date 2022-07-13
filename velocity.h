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
   Velocity(Angle angle, double magnitude);
   
   // getters
   virtual double getX() const { return velocityX; }
   virtual double getY() const { return velocityY; }
   virtual double getSpeed() const;
   
   // mutators
   virtual void applyAcceleration(Acceleration accel, double time);
   void setX(double value) { velocityX = value;  }
   void setY(double value) { velocityY = value;  }
   void addX(double value) { velocityX += value; }
   void addY(double value) { velocityY += value; }
   void set(double valX, double valY)
   {
      velocityX += valX;
      velocityY += valY;
   }
   
   // operators
   const Velocity& operator =  (const Velocity& rhs)
   {
      velocityX = rhs.getX();
      velocityY = rhs.getY();
      return (*this);
   }
   
   const Velocity& operator += (const Velocity& rhs)
   {
      velocityX += rhs.getX();
      velocityY += rhs.getY();
      return *this;
   }
   
   const Velocity& operator + (const Velocity& rhs)
   {
      velocityX += rhs.getX();
      velocityY += rhs.getY();
      return *this;
   }
   
protected:
   double velocityX;    // The horizontal velocity
   double velocityY;    // The vertical velocity
};

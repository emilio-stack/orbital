/***********************************************************************
 * Header File:
 *    Position Doubles : All of the doubles of the position class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    This file provides all the doubles of the position class.
 ************************************************************************/

#pragma once

#include "Position.h"      // For POSITION


/***********************************************************************
 * POSITION DUMMY
 * The double for the position class that verifies it is never used
 ************************************************************************/
class PositionDummy: public Position
{
public:
   // constructor
   PositionDummy(){};
   
   // getters
   virtual double getMetersX()       const { assert(false); }
   virtual double getMetersY()       const { assert(false); }
   virtual double getPixelsX()       const { assert(false); }
   virtual double getPixelsY()       const { assert(false); }

   // setters
   virtual void setMeters(double xMeters, double yMeters)   { assert(false); }
   virtual void setMetersX(double xMeters)                  { assert(false); }
   virtual void setMetersY(double yMeters)                  { assert(false); }
   virtual void setPixelsX(double xPixels)                  { assert(false); }
   virtual void setPixelsY(double yPixels)                  { assert(false); }
   virtual void addMetersX(double dxMeters)                 { assert(false); }
   virtual void addMetersY(double dyMeters)                 { assert(false); }
   virtual void addPixelsX(double dxPixels)                 { assert(false); }
   virtual void addPixelsY(double dyPixels)                 { assert(false); }
   
   // update
   virtual void update(Velocity velocity, Acceleration gravity, double time) { assert(false); }

   // deal with the ratio of meters to pixels
   virtual void setZoom(double metersFromPixels)   { assert(false); }
   virtual double getZoom() const                  { assert(false); }

private:
   // calculate the new value of a component: either X or Y
   virtual double calcComponent(double posComp, double velComp, double accelComp, double time) const
   { assert(false); }
};

/***********************************************************************
 * POSITION FAKE
 * The double for the position class that always is initialized to
 * 0, 42164000.0 and allows X and Y to be set
 ************************************************************************/
class PositionFake: public Position
{
public:
   // constructor
   PositionFake(){};
};


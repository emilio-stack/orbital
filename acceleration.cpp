/***********************************************************************
 * Header File:
 *    Acceleration : Represents a 2-dimensional acceleration in the
 *    orbit simulation
 * Author:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    Tracks the components of a 2-dimensional acceleration, and provides
 *    a simple way to add two accelerations together.
 ************************************************************************/


#include "acceleration.h"  // for the ACCELERATION class

/***********************************************************************
 * ANGLE MAGNITUDE CONSTRUCTOR
 * Constructs an Acceleration from an angle and magnitude
 ************************************************************************/
Acceleration::Acceleration(Angle angle, double magnitude)
{
   // Calculate and set the horizontal and vertical components
   setX(magnitude * sin(angle.getRadian()));
   setY(magnitude * cos(angle.getRadian()));
}

/***********************************************************************
 * ADD ACCELERATION
 * Adds the components of otherAccel to the components of
 * this Acceleration
 ************************************************************************/
void Acceleration::addAcceleration(Acceleration otherAccel)
{
   x += otherAccel.getX();
   y += otherAccel.getY();
};

/**********************************************************************
 * CLOSE ENOUGH:
 *    A method to tell if a computed value is close enough to
 *    the precision we want.
 * Arguments:
 *    computedValue: The value calculated by the program
 *    hardcodeValue: The value with acceptable precision
 ***********************************************************************/
bool Acceleration :: closeEnough(double computedValue, double hardcodeValue) const
{
   return abs(computedValue - hardcodeValue) < 0.0005;
}

/***************************************************************************************
 * Header File:
 *    Angle :
 * Author:
 *    Emilio Regino & Bradley Payne
 * Summary:
 *    Keeps track of an angle, and provides an easy interface to convert to
 *    and from degrees and radians
 ***************************************************************************************/

#include "angle.h"     // for the angle class definition

/*************************************************
 * SET DEGREES
 * A method to set a new angle in degrees
 **************************************************/
void Angle::setDegrees(double newAngleDegrees)
{
   // make sure the angle is valid before assigning
   angle = normalize(newAngleDegrees);
}

/*************************************************
 * CONVERT TO VALID
 * A method to convert an invalid angle to a
 * valid angle.
 **************************************************/
double Angle :: normalize(double newAngle)
{
   // if the angle is greater than 360
   while (newAngle > 360.0)
      // subtract 360 to get the same direction but in the valid range
      newAngle = newAngle - 360.0;

   // if the angle is less than 180
   while (newAngle < 0.0)
      // add 360 to get the same direction but in the valid range
      newAngle = newAngle + 360.0;

   return newAngle;
};

/**********************************************************************
 * CLOSE ENOUGH:
 *    A method to tell if a computed value is close enough to
 *    the precision we want.
 * Arguments:
 *    computedValue: The value calculated by the program
 *    hardcodeValue: The value with acceptable precision
 ***********************************************************************/
bool Angle :: closeEnough(double computedValue, double hardcodeValue) const
{
   return abs(computedValue - hardcodeValue) < 0.0005;
}

/***********************************************************************
 * ASSIGNMENT OPERATOR
 * A method to overload the assignment operator.
 ************************************************************************/
Angle& Angle::operator= (const Angle& rhs)
{
   angle = rhs.angle;
   return *this;
}

/***********************************************************************
 * EQUIVALANCE OPERATOR
 * A method to overload the assignment operator.
 ************************************************************************/
bool Angle::operator== (const Angle& rhs)
{
   return (angle == rhs.angle);
}

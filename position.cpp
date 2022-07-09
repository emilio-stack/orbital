/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include <cassert>


Position::Position(double x, double y) : x(0.0), y(0.0)
{
   setMetersX(x);
   setMetersY(y);
}

/******************************************
 * POSITION UPDATE
 *       Update the position given velocity, acceleration, and time
 *****************************************/
void Position :: update(Velocity velocity, Acceleration accel, double time)
{
   setMetersX(calcComponent(x, velocity.getX(), accel.getX(), time));
   setMetersY(calcComponent(y, velocity.getY(), accel.getY(), time));
}

/******************************************
 * POSITION CALCULATE COMPONENT
 *       Calculate the new value of one of the components of position: either X or Y
 *       it takes the corresponding X or Y component of the velocity and acceleration
 *       passed in as arguments.
 *****************************************/
double Position :: calcComponent(double posComp, double velComp, double accelComp, double time) const
{
   return posComp + (velComp * time) + (0.5 * accelComp * (time * time));
}

/******************************************
 * POINT : ASSIGNMENT
 * Assign a point
 *****************************************/
Position& Position::operator = (const Position& pt)
{
   x = pt.x;
   y = pt.y;
   return *this;
}

/******************************************
 * POSITION insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const Position& pt)
{
   out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
   return out;
}
   
/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, Position& pt)
{
   double x;
   double y;
   in >> x >> y;

   pt.setMetersX(x);
   pt.setMetersY(y);

   return in;
}

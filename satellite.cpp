/***********************************************************************
 * Header File:
 *    Satellite : A generic satellite in Earth's orbit
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    This is not any specific satellite. The main purpose of this
 *    class is to get the orbit working in the simulator
 ************************************************************************/

#include "satellite.h"

const double TIME_DILATION = 24.0 * 60.0; /* 24 hours in a day X 60 minutes in an hour */
const double FRAME_RATE = 30.0;
const double TIME_PER_FRAME = TIME_DILATION / FRAME_RATE;
const double EARTH_RADIUS = 6378000.0;
const double GRAVITY = -9.80665;


/*************************************************************************
 * ALTITUDE ABOVE THE EARTH
 * Compute the height above the earth given the position of an object
 *
 * h = √ (x2 + y2) - r
 * Where:
 *    h = height above the earth in meters
 *    x = horizontal position of the satellite where the center of the earth is 0
 *    y = vertical position of the satellite where the center of the earth is 0
 *    r = radius of the earth: 6,378,000 m
 *************************************************************************/
double computeAltitude(double x, double y)
{
   return sqrt((x * x) + (y * y)) - EARTH_RADIUS;
}

/*************************************************************************
 * COMPUTE GRAVITY
 * Compute the magnitude of acceleration due to gravity at a
 * given altitude
 *
 * gh = g ( r / (r + h)) **2
 * Where:
 *    gh = magnitude of acceleration due to gravity at an altitude (h)
 *    g = gravity at sea level: 9.80665 m/s2
 *    r = radius of the earth: 6,378,000 m
 *    h = height above the earth in meters
 *************************************************************************/
double computeGravity(double h)
{
   double base = (EARTH_RADIUS / (EARTH_RADIUS + h));
   return GRAVITY * (base * base);
}

/*************************************************************************
 * COMPUTE GRAVITY DIRECTION
 * compute the direction of the pull of gravity
 *
 * d = atan(xe - xs, ye - ys)
 * Where:
 *    d = direction of the pull of gravity, in radians
 *    xe = horizontal position of the center of the earth: 0 m
 *    ye = vertical position of the center of the earth: 0 m
 *    xs = horizontal position of the satellite in meters
 *    ys = vertical position of the satellite in meters
 *************************************************************************/
double computeGravityDirection(double xS, double yS)
{
   // -  (-xS) direction is positive
   return atan2(-xS, -yS);  /* -xS is same thing as 0.0 - xS */
}

/*******************************************************************
 *  CALCULATE HORIZONTAL COMPONENT
 *  A function to calculate the horizontal component of acceleration
 *
 *  dx = s sin(a)
 *  Where:
 *    s = overall speed (m/s)
 *    a = directon of travel where 0 is pointing up (radians)
 * *******************************************************************/

double calcHorComp(double speed, double angle)
{
   return speed * sin(angle);
}

/*******************************************************************
 *  CALCULATE VERTICAL COMPONENT
 *  A function to calculate the vertical component of acceleration
 *
 *  dy = s cos(a)
 *  Where:
 *    dy = vertical component of speed (m/s)
 *    s = overall speed (m/s)
 *    a = directon of travel where 0 is pointing up (radians)
 * *******************************************************************/
double calcVertComp(double speed, double angle)
{
   return speed * cos(angle);
}

/*******************************************************************
 *  CALC VELOCITY
 *  A function to calculate velocity with constant acceleration
 *
 *  v = v0 + a t
 *  Where:
 *    v = velocity in meters (m/s)
 *    v0 = initial velocity (m/s)
 *    a = acceleration (m/s2)
 *    t = time (s)
 * *******************************************************************/
double calcVelocity(double velocityInit, double acceleration)
{
   return velocityInit + (acceleration * TIME_PER_FRAME);
}

/*******************************************************************
 *  CALC DISTANCE
 *  A function to calculate distance
 *
 *  s = s0 + v t + ½ a t ** 2
 *  Where:
 *    s = distance in meters (m)
 *    s0 = initial distance (m)
 *    v = velocity (m/s)
 *    t = time (s)
 *    a = acceleration (m/s2)
 * *******************************************************************/
double calcDistance(double distanceInit, double velocity, double acceleration)
{
   return distanceInit + (velocity * TIME_PER_FRAME) + (0.5 * acceleration * (TIME_PER_FRAME *                                                                                   TIME_PER_FRAME));
}

/***********************************************************************
 * UPDATE POSITION
 * A method to handle the logic to update the satellite's position
 ***********************************************************************/
void Satellite::update()
{
   double altitude = computeAltitude(position.getMetersX(), position.getMetersY());
   double gravity = computeGravity(altitude);
   double angle = computeGravityDirection(position.getMetersX(), position.getMetersY());
   double accelerationX = calcHorComp(gravity, angle);
   double accelerationY = calcVertComp(gravity, angle);
   double velocityX = calcVelocity(-2685.0 /* Cathetus */,  accelerationX);
   double velocityY = calcVelocity(1550.0 /* Cathetus */,  accelerationY);
   double newX = calcDistance(position.getMetersX(), velocityX, accelerationX);
   double newY = calcDistance(position.getMetersY(), velocityY, accelerationX);
   position.setMeters(newX, newY);
   this->angle = angle;
   std::cout << position << std::endl;
}



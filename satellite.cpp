/***********************************************************************
 * Header File:
 *    Satellite : A generic satellite in Earth's orbit
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    This is not any specific satellite. The main purpose of this
 *    class is to get the orbit working in the simulator
 ************************************************************************/

#include <cmath>           // for SQRT function
#include "satellite.h"     // for SATELLITE 

const double EARTH_RADIUS = 6378000.0;
const double GRAVITY = 9.80665;

/**********************************************************************
 * SATELLITE DEFAULT CONSTRUCTOR
 **********************************************************************/
Satellite :: Satellite()
{
   position.setMeters(0.0, 0.0);
   angle.setDegrees(0);
   velocity.setX(0.0);
   velocity.setY(0.0);
   angularVelocity = 0.0;
   dead = false;
   radius = 0.0;
}

/**********************************************************************
 * SATELLITE POSITION CONSTRUCTOR
 * constructs a satellite form a position
 **********************************************************************/
Satellite :: Satellite(Position pos)
{
   position.setMeters(pos.getMetersX(), pos.getMetersY());
}

/**********************************************************************
 * UPDATE
 * updates a satellite for a specified unit of time
 **********************************************************************/
void Satellite :: update(double time)
{
   Acceleration gravity(angle, computeGravity());
   velocity.applyAcceleration(gravity, time);
   position.update(velocity, gravity, time);
   angle.addRadian(0.01);
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
double Satellite :: computeGravity() const
{
   double h = computeAltitude();
   return GRAVITY * ((EARTH_RADIUS / (EARTH_RADIUS + h)) * (EARTH_RADIUS / (EARTH_RADIUS + h)));
}

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
double Satellite :: computeAltitude() const
{
   return sqrt((position.getMetersX() * position.getMetersX()) + (position.getMetersY() * position.getMetersY())) - EARTH_RADIUS;
}

/**********************************************************************
 * ATOMIC SATELLITE  CONSTRUCTOR
 * A constructor for an atomic satellite that takes a parent SATELLITE
 * and an ANGLE
 **********************************************************************/
AtomicSatellite :: AtomicSatellite(Satellite & parent, Angle ang)
{
   position = parent.getPosition();
   angle = ang;
}

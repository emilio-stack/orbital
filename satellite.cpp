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

const double ANGULAR_VELOCITY = 0.2;
const double EARTH_RADIUS = 6378000.0;
const double GRAVITY = -9.80665;
//const double TIME_DILATION = 24.0 * 60.0; /* 24 hours in a day X 60 minutes in an hour */
//const double FRAME_RATE = 30.0;
//const double TIME_PER_FRAME = TIME_DILATION / FRAME_RATE;

/**********************************************************************
 * SATELLITE DEFAULT CONSTRUCTOR
 **********************************************************************/
Satellite :: Satellite()
{
   position.setMeters(0.0, 0.0);
   angle = Angle(position.getMetersX(), position.getMetersY());
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
Satellite :: Satellite(Position pos, Velocity init, double rad)
{
   position.setMeters(pos.getMetersX(), pos.getMetersY());
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity = init;
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = rad;
}

/**********************************************************************
 * UPDATE
 * updates a satellite for a specified unit of time
 **********************************************************************/
void Satellite :: update(double time)
{
//   std::cout << "Position:      " << position << std::endl;
   double gravityMagnitude = computeGravity();
//   std::cout << "Magnitude:     " << gravityMagnitude              << std::endl;
   angle = Angle(position.getMetersX(), position.getMetersY());
//   std::cout << "Angle:         " << angle.getRadian() << std::endl;
   Acceleration gravity(angle, gravityMagnitude);
//   std::cout << "Gravity:       " << gravity.getX() << ", " << gravity.getY() << std::endl;
   velocity.applyAcceleration(gravity, time);
//   std::cout << "Velocity:      " << velocity.getX() << ", " << velocity.getY() << std::endl;
   position.update(velocity, gravity, time);
   
   std::cout << std::endl;
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
//   std::cout << "Altitude:      " << h  << std::endl;
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
 * CLOSE ENOUGH:
 *    A method to tell if a computed value is close enough to
 *    the precision we want.
 * Arguments:
 *    computedValue: The value calculated by the program
 *    hardcodeValue: The value with acceptable precision
 ***********************************************************************/
bool Satellite :: closeEnough(double computedValue, double hardcodeValue) const
{
   return abs(computedValue - hardcodeValue) < 0.0005;
}

/**********************************************************************
 * ATOMIC SATELLITE  CONSTRUCTOR
 * A constructor for an atomic satellite that takes a parent SATELLITE
 * and an ANGLE
 **********************************************************************/
AtomicSatellite :: AtomicSatellite(const Satellite & parent, Angle shootOff, double rad)
{
   position = parent.getPosition();
   angle = Angle(position.getMetersX(), position.getMetersY());
   angle.addDegrees(shootOff.getDegrees());
   velocity = parent.getVelocity();
   double magnitude = random(5000, 9000);
   velocity += Velocity(angle, magnitude);
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = rad;
}

/**********************************************************************
 * GPS CONSTRUCTOR
 * constructs a GPS form a POSITION and VELOCITY
 **********************************************************************/
GPS :: GPS(Position pos, Velocity init)
{
   position.setMeters(pos.getMetersX(), pos.getMetersY());
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity = init;
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = 12.0;
}

/**********************************************************************
 * GPS DESTROY
 * Upon collision GPS satellites create 2 fragments
 * and 3 parts: GPS CENETR, GPS  LEFT, GPS RIGHT
 **********************************************************************/
void GPS :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   GPSCenter center(*this, Angle(30.0), 7.0);
   GPSLeft left(*this, Angle(45.0), 8.0);
   GPSRight right(*this, Angle(270.0), 8.0);
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
   satellites.push_back(&center);
   satellites.push_back(&left);
   satellites.push_back(&right);
}

/**********************************************************************
 * HUBBLE DEFAULT CONSTRUCTOR
 **********************************************************************/
Hubble :: Hubble()
{
   position.setMeters(0.0, -42164000.0);
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity.setX(3100.0);
   velocity.setY(0.0);
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = 10;
}

/**********************************************************************
 * HUBBLE DESTROY
 * Upon collision HUBBLE satellites create 0 fragments
 * and 4 parts: HUBBLE TELESCOPE, HUBBLE COMPUTER,
 * HUBBLE  LEFT, HUBBLE RIGHT
 **********************************************************************/
void Hubble :: destroy(std::vector<Satellite *> & satellites) const
{
   HubbleTelescope tel(*this, Angle(0.0), 10.0);
   HubbleComputer comp(*this, Angle(90.0), 7.0);
   HubbleLeft left(*this, Angle(45.0), 8.0);
   HubbleRight right(*this, Angle(270.0), 8.0);
   satellites.push_back(&tel);
   satellites.push_back(&comp);
   satellites.push_back(&left);
   satellites.push_back(&right);
}

/**********************************************************************
 * SPUTNIK DEFAULT CONSTRUCTOR
 **********************************************************************/
Sputnik :: Sputnik()
{
   position.setMeters(-36515095.13 , 21082000.0);
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity.setX(2050.0);
   velocity.setY(2684.68);
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = 4;
}

/**********************************************************************
 * SPUTNIK DESTROY
 * Upon collision SPUTNIK satellites create 4 fragments and 0 parts
 **********************************************************************/
void Sputnik :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   Fragment frag3(*this, Angle(180.0));
   Fragment frag4(*this, Angle(270.0));
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
   satellites.push_back(&frag3);
   satellites.push_back(&frag4);
}

/**********************************************************************
 * STARLINK DEFAULT CONSTRUCTOR
 **********************************************************************/
Starlink :: Starlink()
{
   position.setMeters(0.0 , -13020000.0);
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity.setX(5800.0);
   velocity.setY(0.0);
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = 6;
}

/**********************************************************************
 * STARLINK DESTROY
 * Upon collision STARLINK satellites create 2 fragments
 * and 2 parts: STARLINK BODY, STARLINK ARRAY
 **********************************************************************/
void Starlink :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   StarlinkBody body(*this, Angle(30.0), 2.0);
   StarlinkArray arr(*this, Angle(45.0), 4.0);
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
   satellites.push_back(&body);
   satellites.push_back(&arr);
}

/**********************************************************************
 * SHIP DEFAULT CONSTRUCTOR
 **********************************************************************/
Ship :: Ship()
{
   position.setPixelsX(-450.0);
   position.setPixelsY(450.0);
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity.setX(0.0);
   velocity.setY(-2000);
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = 6;
   thrust = false;
}

/**********************************************************************
 * SHIP DESTROY
 * Upon collision SHIP satellites create 3 fragments and 0 parts
 **********************************************************************/
void Ship :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   Fragment frag3(*this, Angle(180.0));
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
   satellites.push_back(&frag3);
}

/**********************************************************************
 * SHIP INPUT
 * SHIP satellites handle input differently than other satellites:
 *    Up: Accelerate
 *    Left: rotate left by 0.1 radians
 *    Right: rotate right by 0.1 radians
 *    Space: shoot projectile
 **********************************************************************/
void Ship :: input(Interface ui, std::vector<Satellite *> & satellites)
{
   // left & right input
   angle.addRadian((ui.isRight() ? 0.1 : 0.0) + (ui.isLeft() ? -0.1 : 0.0));
   
   // down input
   if (ui.isDown())
   {
      thrust = true;
      Acceleration addidtionalAccel (angle, 30.0);
      velocity.applyAcceleration(addidtionalAccel, TIME_PER_FRAME);
   }

   // space input
   if (ui.isSpace())
   {
      Velocity vBullet (angle, 9000.0);
      Projectile bullet(*this, vBullet);
      satellites.push_back(&bullet);
   }
}

/**********************************************************************
 * DRAGON DEFAULT CONSTRUCTOR
 **********************************************************************/
Dragon :: Dragon()
{
   position.setMeters(0.0, 8000000.0);
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity.setX(-7900.0);
   velocity.setY(0.0);
   angularVelocity = ANGULAR_VELOCITY;
   dead = false;
   radius = 7;
}

/**********************************************************************
 * DRAGON DESTROY
 * Upon collision DRAGON satellites create 2 fragments
 * and 3 parts: DRAGON CENETR, DRAGON  LEFT, DRAGON RIGHT
 **********************************************************************/
void Dragon :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   DragonCenter center(*this, Angle(30.0), 6.0);
   DragonLeft left(*this, Angle(45.0), 6.0);
   DragonRight right(*this, Angle(270.0), 6.0);
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
   satellites.push_back(&center);
   satellites.push_back(&left);
   satellites.push_back(&right);
}

/**********************************************************************
 * DRAGON CENTER DESTROY
 * Upon collision DRAGON CENTER satellites create 4 fragments
 * and 0 parts.
 **********************************************************************/
void DragonCenter :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   Fragment frag3(*this, Angle(180.0));
   Fragment frag4(*this, Angle(270.0));
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
   satellites.push_back(&frag3);
   satellites.push_back(&frag4);
}

/**********************************************************************
 * DRAGON LEFT DESTROY
 * Upon collision DRAGON LEFT satellites create 2 fragments
 * and 0 parts.
 **********************************************************************/
void DragonLeft :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
}

/**********************************************************************
 * DRAGON RIGHT DESTROY
 * Upon collision DRAGON RIGHT satellites create 2 fragments
 * and 0 parts.
 **********************************************************************/
void DragonRight :: destroy(std::vector<Satellite *> & satellites) const
{
   Fragment frag1(*this, Angle(0.0));
   Fragment frag2(*this, Angle(90.0));
   satellites.push_back(&frag1);
   satellites.push_back(&frag2);
}

/**********************************************************************
 * FRAGMENT SATELLITE  CONSTRUCTOR
 * A constructor for an fragment satellite that takes a parent SATELLITE
 * and an ANGLE
 **********************************************************************/
Fragment :: Fragment(const Satellite & parent, Angle shootOff)
{
   position = parent.getPosition();
   angle = Angle(position.getMetersX(), position.getMetersY());
   angle.addDegrees(shootOff.getDegrees());
   velocity = parent.getVelocity();
   double magnitude = random(5000, 9000);
   velocity += Velocity(angle, magnitude);
   angularVelocity = 1.0;   // much faster than ANGULAR_VELOCITY
   dead = false;
   radius = 2.0;
   lifeSpan = random(2.0, 3.0);
   aliveTime = 0.0;
}

/**********************************************************************
 * PROJECTILE SATELLITE  CONSTRUCTOR
 * A constructor for an projectile satellite that takes a parent SHIP SATELLITE
 * and an ANGLE
 **********************************************************************/
Projectile :: Projectile(const Ship & parent, Velocity bullet)
{
   position = parent.getPosition();
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity = bullet;
   angularVelocity = 0.0;   // projectile does not have an angular velocity
   dead = false;
   radius = 0.5;
   lifeSpan = 2.0;
   aliveTime = 0.0;
}

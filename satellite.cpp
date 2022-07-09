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
   radius = 0.0 * position.getZoom();
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
   radius = rad * position.getZoom();
}

/**********************************************************************
 * UPDATE
 * updates a satellite for a specified unit of time
 **********************************************************************/
void Satellite :: update(double time)
{
   double gravityMagnitude = computeGravity();
   angle = Angle(position.getMetersX(), position.getMetersY());
   Acceleration gravity(angle, gravityMagnitude);
   velocity.applyAcceleration(gravity, time);
   position.update(velocity, gravity, time);
   angle.addRadian(angularVelocity);
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
   radius = rad * position.getZoom();
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
   radius = 12.0 * position.getZoom();
}

/**********************************************************************
 * GPS DESTROY
 * Upon collision GPS satellites create 2 fragments
 * and 3 parts: GPS CENETR, GPS  LEFT, GPS RIGHT
 **********************************************************************/
void GPS :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   Satellite * center = new GPSCenter(*this, Angle(30.0), 7.0);
   Satellite * left = new GPSLeft(*this, Angle(45.0), 8.0);
   Satellite * right = new GPSRight(*this, Angle(270.0), 8.0);
   satellites.push_back(frag1);
   satellites.push_back(frag2);
   satellites.push_back(center);
   satellites.push_back(left);
   satellites.push_back(right);
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
   radius = 10.0 * position.getZoom();
}

/**********************************************************************
 * HUBBLE DESTROY
 * Upon collision HUBBLE satellites create 0 fragments
 * and 4 parts: HUBBLE TELESCOPE, HUBBLE COMPUTER,
 * HUBBLE  LEFT, HUBBLE RIGHT
 **********************************************************************/
void Hubble :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * tel = new HubbleTelescope(*this, Angle(0.0), 10.0);
   Satellite * comp = new HubbleComputer(*this, Angle(90.0), 7.0);
   Satellite * left = new HubbleLeft(*this, Angle(45.0), 8.0);
   Satellite * right = new HubbleRight(*this, Angle(270.0), 8.0);
   satellites.push_back(tel);
   satellites.push_back(comp);
   satellites.push_back(left);
   satellites.push_back(right);
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
   radius = 4.0 * position.getZoom();
}

/**********************************************************************
 * SPUTNIK DESTROY
 * Upon collision SPUTNIK satellites create 4 fragments and 0 parts
 **********************************************************************/
void Sputnik :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   Satellite * frag3 = new Fragment(*this, Angle(180.0));
   Satellite * frag4 = new Fragment(*this, Angle(270.0));
   satellites.push_back(frag1);
   satellites.push_back(frag2);
   satellites.push_back(frag3);
   satellites.push_back(frag4);
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
   radius = 6.0 * position.getZoom();
}

/**********************************************************************
 * STARLINK DESTROY
 * Upon collision STARLINK satellites create 2 fragments
 * and 2 parts: STARLINK BODY, STARLINK ARRAY
 **********************************************************************/
void Starlink :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   Satellite * body = new StarlinkBody(*this, Angle(30.0), 2.0);
   Satellite * arr = new StarlinkArray(*this, Angle(45.0), 4.0);
   satellites.push_back(frag1);
   satellites.push_back(frag2);
   satellites.push_back(body);
   satellites.push_back(arr);
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
   radius = 6.0 * position.getZoom();
   thrust = false;
}

/**********************************************************************
 * SHIP DESTROY
 * Upon collision SHIP satellites create 3 fragments and 0 parts
 **********************************************************************/
void Ship :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   Satellite * frag3 = new Fragment(*this, Angle(180.0));
   satellites.push_back(frag1);
   satellites.push_back(frag2);
   satellites.push_back(frag3);
}

/**********************************************************************
 * SHIP INPUT
 * SHIP satellites handle input differently than other satellites:
 *    Up: Accelerate
 *    Left: rotate left by 0.1 radians
 *    Right: rotate right by 0.1 radians
 *    Space: shoot projectile
 **********************************************************************/
void Ship :: input(const Interface* pUI, std::vector<Satellite *> & satellites)
{
   // left & right input
   angularVelocity += (pUI->isRight() ? 0.1 : 0.0) + (pUI->isLeft() ? -0.1 : 0.0);
   
   // down input
   if (pUI->isDown())
   {
      thrust = true;
      Acceleration addidtionalAccel (angle, 30.0);
      velocity.applyAcceleration(addidtionalAccel, TIME_PER_FRAME);
   } else
      thrust = false;

   // space input
   if (pUI->isSpace())
   {
      Velocity vBullet (angle, 9000.0);
      Satellite * pBullet = new Projectile (*this, vBullet);
      satellites.push_back(pBullet);
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
   radius = 7.0 * position.getZoom();
}

/**********************************************************************
 * DRAGON DESTROY
 * Upon collision DRAGON satellites create 2 fragments
 * and 3 parts: DRAGON CENETR, DRAGON  LEFT, DRAGON RIGHT
 **********************************************************************/
void Dragon :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   Satellite * center = new DragonCenter(*this, Angle(30.0), 6.0);
   Satellite * left = new DragonLeft(*this, Angle(45.0), 6.0);
   Satellite * right = new DragonRight(*this, Angle(270.0), 6.0);
   satellites.push_back(frag1);
   satellites.push_back(frag2);
   satellites.push_back(center);
   satellites.push_back(left);
   satellites.push_back(right);
}

/**********************************************************************
 * DRAGON CENTER DESTROY
 * Upon collision DRAGON CENTER satellites create 4 fragments
 * and 0 parts.
 **********************************************************************/
void DragonCenter :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   Satellite * frag3 = new Fragment(*this, Angle(180.0));
   Satellite * frag4 = new Fragment(*this, Angle(270.0));
   satellites.push_back(frag1);
   satellites.push_back(frag2);
   satellites.push_back(frag3);
   satellites.push_back(frag4);
}

/**********************************************************************
 * DRAGON LEFT DESTROY
 * Upon collision DRAGON LEFT satellites create 2 fragments
 * and 0 parts.
 **********************************************************************/
void DragonLeft :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   satellites.push_back(frag1);
   satellites.push_back(frag2);
}

/**********************************************************************
 * DRAGON RIGHT DESTROY
 * Upon collision DRAGON RIGHT satellites create 2 fragments
 * and 0 parts.
 **********************************************************************/
void DragonRight :: destroy(std::vector<Satellite *> & satellites) const
{
   Satellite * frag1 = new Fragment(*this, Angle(0.0));
   Satellite * frag2 = new Fragment(*this, Angle(90.0));
   satellites.push_back(frag1);
   satellites.push_back(frag2);
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
   radius = 2.0 * position.getZoom();
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
   position.addPixelsY(19.0);
   angle = Angle(position.getMetersX(), position.getMetersY());
   velocity = bullet;
   angularVelocity = 0.0;   // projectile does not have an angular velocity
   dead = false;
   radius = 0.5 * position.getZoom();
   lifeSpan = 2.0;
   aliveTime = 0.0;
}

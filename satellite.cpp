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
   // position defaults to (0.0, 0.0)
   position.setMeters(0.0, 0.0);
   
   // calculate the angle at our position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // velocity init is (0.0, 0.0)
   velocity.set(0.0, 0.0);

   // how fast we are spinning in radians per frame
   angularVelocity = 0.0;
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever 0.0 pixels is
   radius = 0.0 * position.getZoom();
}

/**********************************************************************
 * SATELLITE POSITION CONSTRUCTOR
 * constructs a satellite form a position
 **********************************************************************/
Satellite :: Satellite(Position pos, Velocity init, double rad)
{
   // set the position
   position.setMeters(pos.getMetersX(), pos.getMetersY());
   
   // calculate the angle from the position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // set the init velocity
   velocity = init;
   
   // how fast we are spinning
   angularVelocity = ANGULAR_VELOCITY;
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever rad pixels is
   radius = rad * position.getZoom();
}

/**********************************************************************
 * UPDATE
 * updates a satellite for a specified unit of time
 **********************************************************************/
void Satellite :: update(double time)
{
   // the direction of the pull of gravity
   double gravityMagnitude = computeGravity();
   
   // next calculate the angle based on our position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // then calculate the acceleration of gravity
   Acceleration gravity(angle, gravityMagnitude);
   
   // apply acceleration of gravity to our velocity over time
   velocity.applyAcceleration(gravity, time);
   
   // update our position with our new velocity and acceleration over time
   position.update(velocity, gravity, time);
   
   // update our angle from angular velocity
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
   double height = computeAltitude();
   return GRAVITY * ((EARTH_RADIUS / (EARTH_RADIUS + height)) * (EARTH_RADIUS / (EARTH_RADIUS + height)));
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
   // start at parent's position
   position = parent.getPosition();

   // the orientation will be random
   angle = Angle(random(0.0, 360.0));

   // take parent's velocity
   velocity = parent.getVelocity();

   // magnitude of the kick in the direction of the shootoff
   double magnitude = random(50, 90);

   // adjust the velocity to take that of the kick/shootoff
   velocity += Velocity(angle, magnitude);

   // how fast we are spinning in radians per frame
   angularVelocity = ANGULAR_VELOCITY;
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever rad pixels is
   radius = rad * position.getZoom();
}

/**********************************************************************
 * GPS CONSTRUCTOR
 * constructs a GPS form a POSITION and VELOCITY
 **********************************************************************/
GPS :: GPS(Position pos, Velocity init)
{
   // start at our specified position
   position.setMeters(pos.getMetersX(), pos.getMetersY());
   
   // calculate our angle from our position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // set our specified initial velocity
   velocity = init;
   
   // how fast we are spinning in radians per frame
   angularVelocity = ANGULAR_VELOCITY;
   
   // not deaed yet!
   dead = false;
   
   // radius in meters, whatever 12 pixels is
   radius = 12.0 * position.getZoom();
}

/**********************************************************************
 * GPS DESTROY
 * Upon collision GPS satellites create 2 fragments
 * and 3 parts: GPS CENETR, GPS  LEFT, GPS RIGHT
 **********************************************************************/
void GPS :: destroy(std::list<Satellite *> & satellites) const
{
   // create the parts and fragments
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   Satellite * center = new GPSCenter(*this, Angle(30.0), 7.0);
   Satellite * left = new GPSLeft(*this, Angle(45.0), 8.0);
   Satellite * right = new GPSRight(*this, Angle(270.0), 8.0);
   
   // offset the parts and fragments
   frag1->update(144);
   frag2->update(144);
   center->update(144);
   left->update(144);
   right->update(144);
   
   // add them to the list of satellites
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
   // default position is (0.0, -42164000.0)
   position.setMeters(0.0, -42164000.0);
   
   // calculate angle at that position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // set our initial velocity (3100.0, 0.0)
   velocity.set(3100.0, 0.0);
   
   // how fast we are spinning in radian per frame
   angularVelocity = ANGULAR_VELOCITY;
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever 12 pixels is
   radius = 10.0 * position.getZoom();
}

/**********************************************************************
 * HUBBLE DESTROY
 * Upon collision HUBBLE satellites create 0 fragments
 * and 4 parts: HUBBLE TELESCOPE, HUBBLE COMPUTER,
 * HUBBLE  LEFT, HUBBLE RIGHT
 **********************************************************************/
void Hubble :: destroy(std::list<Satellite *> & satellites) const
{
   // Create the parts
   Satellite * tel = new HubbleTelescope(*this, Angle(0.0), 10.0);
   Satellite * comp = new HubbleComputer(*this, Angle(90.0), 7.0);
   Satellite * left = new HubbleLeft(*this, Angle(45.0), 8.0);
   Satellite * right = new HubbleRight(*this, Angle(270.0), 8.0);
   
   // offset the parts
   tel->update(144);
   comp->update(144);
   left->update(144);
   right->update(144);
   
   // add them to the list of satellites
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
   // default position is (-36515095.13 , 21082000.0)
   position.setMeters(-36515095.13 , 21082000.0);
   
   // calculate the angle from our position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // set the initial velocity
   velocity.set(2050.0, 2684.68);
   
   // how fast we are spinning in radians per frame
   angularVelocity = ANGULAR_VELOCITY;
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever 12 pixels is
   radius = 4.0 * position.getZoom();
}

/**********************************************************************
 * SPUTNIK DESTROY
 * Upon collision SPUTNIK satellites create 4 fragments and 0 parts
 **********************************************************************/
void Sputnik :: destroy(std::list<Satellite *> & satellites) const
{
   // create the parts and fragments
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   Satellite * frag3 = new Fragment(*this);
   Satellite * frag4 = new Fragment(*this);
   
   // offset the parts and fragments
   frag1->update(144);
   frag2->update(144);
   frag3->update(144);
   frag4->update(144);
   
   // add them to the list of satellites
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
   // this is the default position of starlink
   position.setMeters(0.0 , -13020000.0);
   
   // calculate the angle from the position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // the initial velocity of of the starlink
   velocity.setX(5800.0);
   velocity.setY(0.0);
   
   // how fast we are spinning in radians
   angularVelocity = ANGULAR_VELOCITY;
   
   // not dead yet!
   dead = false;
   
   // radius whatever 6.0 pixels times zoom is
   radius = 6.0 * position.getZoom();
}

/**********************************************************************
 * STARLINK DESTROY
 * Upon collision STARLINK satellites create 2 fragments
 * and 2 parts: STARLINK BODY, STARLINK ARRAY
 **********************************************************************/
void Starlink :: destroy(std::list<Satellite *> & satellites) const
{
   // create the satellites and parts
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   Satellite * body = new StarlinkBody(*this, Angle(30.0), 2.0);
   Satellite * arr = new StarlinkArray(*this, Angle(45.0), 4.0);
   
   // offset the satellites and parts
   frag1->update(144);
   frag2->update(144);
   body->update(144);
   arr->update(144);
   
   // add them to the list of satellites
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
   // Ship's default position is (-450px, 450px)
   position.setPixelsX(-450.0);
   position.setPixelsY(450.0);
   
   // Calculate the angle from the position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // initial velocity is (0.0 m/s, -2,000 m/s)
   velocity.set(0.0, -2000.0);

   // how fast are we spinning. This is radian per frame
   angularVelocity = ANGULAR_VELOCITY;
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever 2 pixels is
   radius = 6.0 * position.getZoom();
   
   // ship is not thrusting by default
   thrust = false;
}

/**********************************************************************
 * SHIP DESTROY
 * Upon collision SHIP satellites create 3 fragments and 0 parts
 **********************************************************************/
void Ship :: destroy(std::list<Satellite *> & satellites) const
{
   // create the fragments
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   Satellite * frag3 = new Fragment(*this);
   
   // offset the fragments
   frag1->update(144);
   frag2->update(144);
   frag3->update(144);
   
   // add them to the list of satellites
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
void Ship :: input(const Interface* pUI, std::list<Satellite *> & satellites)
{
   // left & right input
   angularVelocity += (pUI->isRight() ? 0.1 : 0.0) + (pUI->isLeft() ? -0.1 : 0.0);
   
   // down input
   if (pUI->isDown())
   {
      // set thrust to true and apply the additional thrust acceleration
      thrust = true;
      Acceleration addidtionalAccel (angle, 3.0);
      velocity.applyAcceleration(addidtionalAccel, TIME_PER_FRAME);
   } else
      // set thrust back to false
      thrust = false;

   // space input
   if (pUI->isSpace())
   {
      // create the bullet velocity
      Velocity vBullet (angle, 9000.0);
      
      // create the bullet
      Satellite * pBullet = new Projectile (*this, vBullet);
      
      // offset the bullet
      pBullet->update(144);
      
      // add the bullet to the list of satellites
      satellites.push_back(pBullet);
   }
}

/**********************************************************************
 * DRAGON DEFAULT CONSTRUCTOR
 **********************************************************************/
Dragon :: Dragon()
{
   // Dragon default position starts at (0.0, 8000000.0)
   position.setMeters(0.0, 8000000.0);
   
   // Calculate the orientation from the position
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // Dragon initial velocity is (-7,900.0 m/s, 0.0 m/s) by default
   velocity.set(-7900.0, 0.0);
   
   // how fast are we spinning. This is radian per frame
   angularVelocity = ANGULAR_VELOCITY;
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever 2 pixels is
   radius = 7.0 * position.getZoom();
}

/**********************************************************************
 * DRAGON DESTROY
 * Upon collision DRAGON satellites create 2 fragments
 * and 3 parts: DRAGON CENETR, DRAGON  LEFT, DRAGON RIGHT
 **********************************************************************/
void Dragon :: destroy(std::list<Satellite *> & satellites) const
{
   // create the parts and fragments
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   Satellite * center = new DragonCenter(*this, Angle(30.0), 6.0);
   Satellite * left = new DragonLeft(*this, Angle(45.0), 6.0);
   Satellite * right = new DragonRight(*this, Angle(270.0), 6.0);
   
   // offset them
   frag1->update(144);
   frag2->update(144);
   center->update(144);
   left->update(144);
   right->update(144);
   
   // add them to the list of satellites
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
void DragonCenter :: destroy(std::list<Satellite *> & satellites) const
{
   // create the fragments
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   Satellite * frag3 = new Fragment(*this);
   Satellite * frag4 = new Fragment(*this);
   
   // offset the fragments
   frag1->update(144);
   frag2->update(144);
   frag3->update(144);
   frag4->update(144);
   
   // add them to the list of satellites
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
void DragonLeft :: destroy(std::list<Satellite *> & satellites) const
{
   // create the fragments
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   
   // offset the fragments
   frag1->update(144);
   frag2->update(144);
   
   //add them to the list of satellites
   satellites.push_back(frag1);
   satellites.push_back(frag2);
}

/**********************************************************************
 * DRAGON RIGHT DESTROY
 * Upon collision DRAGON RIGHT satellites create 2 fragments
 * and 0 parts.
 **********************************************************************/
void DragonRight :: destroy(std::list<Satellite *> & satellites) const
{
   // create the new fragments
   Satellite * frag1 = new Fragment(*this);
   Satellite * frag2 = new Fragment(*this);
   
   // offset the fragments
   frag1->update(144);
   frag2->update(144);
   
   // add them to the list of satellites
   satellites.push_back(frag1);
   satellites.push_back(frag2);
}

/**********************************************************************
 * FRAGMENT SATELLITE  CONSTRUCTOR
 * A constructor for an fragment satellite that takes a parent SATELLITE
 * and an ANGLE
 **********************************************************************/
Fragment :: Fragment(const Satellite & parent)
{
   // start at the same location as my parent from which I am generated
   position = parent.getPosition();
   
   // the orientation of the fragment will be random
   angle.setDegrees(random(0.0, 360.0));
   
   // start with the parents velocity
   velocity = parent.getVelocity();
   
   // magnitude of the kick in the direction of shootOff
   double magnitude = random(5000, 9000);
   
   // adjust the velocity to take that of the kick/shootooff
   velocity += Velocity(angle, magnitude);
   
   // how fast are we spinning. This is 1 radian per frame
   angularVelocity = 1.0;   // much faster than ANGULAR_VELOCITY
   
   // not dead yet!
   dead = false;
   
   // radius in meters, whatever 2 pixels is
   radius = 2.0 * position.getZoom();
   
   // how many frames until we die
   lifeSpan = random(2.0, 3.0);
   
   // how long have I been alive
   aliveTime = 0.0;
}

/**********************************************************************
 * PROJECTILE SATELLITE  CONSTRUCTOR
 * A constructor for an projectile satellite that takes a parent SHIP SATELLITE
 * and an ANGLE
 **********************************************************************/
Projectile :: Projectile(const Ship & parent, Velocity bullet)
{
   // start at the same location as my parent from which I am generated
   position = parent.getPosition();
   
   // the orientation of the projectile will be random
   angle = Angle(position.getMetersX(), position.getMetersY());
   
   // start with the parents velocity + the velocity of the bullet
   velocity = bullet + parent.getVelocity();
   
   // projectile does not have an angular velocity
   angularVelocity = 0.0;
   
   // not dead yet
   dead = false;
   
   // radius in meters, whatever 2 pixels is
   radius = 0.5 * position.getZoom();
   
   // how many frames until we die
   lifeSpan = 2.0;
   
   // how long have I been alive
   aliveTime = 0.0;
}

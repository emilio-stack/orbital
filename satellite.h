/***********************************************************************
 * Header File:
 *    Satellite : A generic satellite in Earth's orbit
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    This is not any specific satellite. The main purpose of this
 *    class is to get the orbit working in the simulator
 ************************************************************************/

/**
 * TODO: offset is 0 when there it is not attached to a parent but the parent sets the offset when it is attached and called in the parent draw.
 * TODO: implement expiration of projectille and fragment
 */

#pragma once

#include "position.h"      // for POSITION
#include "angle.h"         // for SATELLITE
#include "velocity.h"      // for VELOCITY
#include "uiDraw.h"        // for DRAW *
#include "uiInteract.h"    // for INTERFACE
#include "constants.h"     // for CONSTANTS
#include <list>            // for LIST

/**********************************************************************
 * SATELLITE
 * An abstract base class for satellites in the orbit simulator.
 **********************************************************************/
class Satellite
{
   
public:
   // test class is a friend for private access
   friend class TestSatellite;
   
   // constructor
   Satellite();
   Satellite(Position pos, Velocity init, double radius = 0.0);
   
   // accessors
   Position getPosition()  const { return position;   }
   Velocity getVelocity()  const { return velocity;   }
   double getAngle() const { return angle.getDegrees(); }
   double getRadius()      const { return radius;     }
   bool isDead()           const { return dead;       }

   // mutators
   void kill() { dead =  true; }
   virtual void update(double time);
   virtual bool hasExpired() const { return  false; }
   virtual void age(double amountSeconds) { /* Only expiring satellites age */}
   
   // input & output
   virtual void draw() const = 0;
   virtual void destroy(std::list<Satellite *> & satellites) const = 0;
   virtual void input(const Interface* pUI, std::list<Satellite *> & satellites)
   { /* all satellites ignore input except for ship */ }
   
protected:
   Position position;               // the position of the satellite
   Angle angle;                     // the angle of the satellite
   Velocity velocity;               // the velocity of the satellite
   double angularVelocity;          // the speed of rotation of the satellite in radian
   bool dead;                       // the dead/alive state of the satellite
   double radius;                   // the radius of the satellite in pixels
   
private:
   double computeGravity() const;
   double computeAltitude() const;
   bool closeEnough(double computedValue, double hardcodeValue) const;
};

/**********************************************************************
 * SPUTNIK SATELLITE
 * The sputnik satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Sputnik: public Satellite
{
public:
   Sputnik();
   
   // Upon collision create parts & fragments if any
   void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawSputnik(position, angularVelocity); }
};

/**********************************************************************
 * GPS SATELLITE
 * A GPS satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class GPS: public Satellite
{
public:
   using Satellite :: Satellite;
   GPS(Position pos, Velocity init);
   
   // Upon collision create parts & fragments if any
   void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawGPS(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE SATELLITE
 * The hubble satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Hubble: public Satellite
{
public:
   Hubble();
   
   // Upon collision create parts & fragments if any
   void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawHubble(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON SATELLITE
 * The sputnik satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Dragon: public Satellite
{
public:
   Dragon();
   
   // Upon collision create parts & fragments if any
   void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawCrewDragon(position, angularVelocity); }
};

/**********************************************************************
 * STARLINK SATELLITE
 * A starlink satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Starlink: public Satellite
{
public:
   Starlink();
   
   // Upon collision create parts & fragments if any
   void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawStarlink(position, angularVelocity); }
};

/**********************************************************************
 * SHIP SATELLITE
 * The ship satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Ship: public Satellite
{
public:
   Ship();
   
   // Handle input
   void input(const Interface* pUI, std::list<Satellite *> & satellites);
   
   // Upon collision create parts & fragments if any
   void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawShip(position, angle.getRadian(), thrust); }
   
private:
   bool thrust;   // is the ship thrusting
};

/**********************************************************************
 * ATOMIC SATELLITE
 * An abstract base class for satellites that do not break into
 * more satellites. Inherits from Satellite
 **********************************************************************/
class AtomicSatellite : public Satellite
{
public:
   // test class is a friend for private access
   friend class TestSatellite;
   
   // constructor
   using Satellite :: Satellite;   
   AtomicSatellite(const Satellite & parent, Angle shootOff, double rad);
   
   // Upon collision create parts & fragments if any
   virtual void destroy(std::list<Satellite *> & satellites) const
   { /* Atomics do not break into more satellites */}
};

/**********************************************************************
 * EXPIRING SATELLITE
 * An abstract base class for satellites that do not break into
 * more satellites. Inherits from Atomic Satellite
 **********************************************************************/
class ExpiringSatellite : public AtomicSatellite
{
public:
   // test class is a friend for private access
   friend class TestSatellite;
   
   // constructor
   using AtomicSatellite :: AtomicSatellite;
   
   // check if the satellite has expired
   bool hasExpired() const { return  aliveTime >= lifeSpan; }
   
   // add seconds to the age of a satellite
   void age(double amountSeconds) { aliveTime += amountSeconds; }
   
protected:
   double lifeSpan;        // the life span of the satellite in seconds
   double aliveTime;       // the age of the satellite in seconds
};


/**********************************************************************
 * FRAGMENT
 * A fragment in the orbital simulator. Inherits from Expiring Satellite
 **********************************************************************/
class Fragment: public ExpiringSatellite
{
public:
   using ExpiringSatellite :: ExpiringSatellite;
   Fragment(const Satellite & parent);
   void draw() const { drawFragment(position, angularVelocity); }
};

/**********************************************************************
 * PROJECTILLE
 * A projectille in the orbital simulator. Inherits from Expiring Satellite
 **********************************************************************/
class Projectile: public ExpiringSatellite
{
public:
   using ExpiringSatellite :: ExpiringSatellite;
   Projectile(const Ship & parent, Velocity bullet);
   void draw() const { drawProjectile(position); }
};

/**********************************************************************
 * GPS CENTER
 * A part in the orbital simulator created when a GPS is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class GPSCenter: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   void draw() const { drawGPSCenter(position, angularVelocity); }
};

/**********************************************************************
 * GPS RIGHT
 * A part in the orbital simulator created when a GPS is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class GPSRight: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawGPSRight(position, angularVelocity, position); }
};

/**********************************************************************
 * GPS LEFT
 * A part in the orbital simulator created when a GPS is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class GPSLeft: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawGPSRight(position, angularVelocity, position); }
};

/**********************************************************************
 * HUBBLE TELESCOPE
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class HubbleTelescope: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawHubbleTelescope(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE COMPUTER
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class HubbleComputer: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawHubbleComputer(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE LEFT
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class HubbleLeft: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawHubbleLeft(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE RIGHT
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class HubbleRight: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawHubbleRight(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON CENTER
 * A part in the orbital simulator created when DRAGON  is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class DragonCenter: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   // Upon collision create parts & fragments if any
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawCrewDragonCenter(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON RIGHT
 * A part in the orbital simulator created when DRAGON  is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class DragonRight: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   // Upon collision create parts & fragments if any
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawCrewDragonRight(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON LEFT
 * A part in the orbital simulator created when DRAGON  is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class DragonLeft: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   // Upon collision create parts & fragments if any
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   void draw() const { drawCrewDragonLeft(position, angularVelocity); }
};

/**********************************************************************
 * STARLINK BODY
 * A part in the orbital simulator created when STARLINK is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class StarlinkBody: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawStarlinkBody(position, angularVelocity); }
};

/**********************************************************************
 * STARLINK ARRAY
 * A part in the orbital simulator created when STARLINK is destroyed.
 * Inherits from ATOMIC SATELLITE
 **********************************************************************/
class StarlinkArray: public AtomicSatellite
{
public:
   using AtomicSatellite :: AtomicSatellite;
   
   void draw() const { drawStarlinkArray(position, angularVelocity); }
};

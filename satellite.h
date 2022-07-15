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
 * TODO: Make earth collideable
 * TODO: implement expiration
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
   Satellite(const Satellite & parent, Angle shootoff, double rad);     // the satellite parent constructor
   
   // accessors
   Position getPosition()  const { return position;   }
   Velocity getVelocity()  const { return velocity;   }
   double getAngle() const { return angle.getDegrees(); }
   double getRadius()      const { return radius;     }
   bool isDead()           const { return dead;       }

   // mutators
   void kill() { dead =  true; }
   virtual void update(double time);
   virtual bool hasExpired() const { return  false; /* Only atomic satellites expire */}
   virtual void age(double amountSeconds) { /* Only atomic satellites age */}
   
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
   // Constructor
   Sputnik();
   
   // Must reimplement for sputnik specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for sputnik specific draw
   void draw() const { drawSputnik(position, angularVelocity); }
};

/**********************************************************************
 * GPS SATELLITE
 * A GPS satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class GPS: public Satellite
{
public:
   // Constructor
   GPS(Position pos, Velocity init);
   
   // Must reimplement for GPS specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for GPS specific
   void draw() const { drawGPS(position, angularVelocity); }
};

/**********************************************************************
 * GPS CENTER
 * A part in the orbital simulator created when a GPS is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class GPSCenter: public Satellite
{
public:
   using Satellite :: Satellite;  // for use of satellite parent constructor
   
   // Must reimplement for GPS Center specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for GPS Center specific draw
   void draw() const { drawGPSCenter(position, angularVelocity); }
};

/**********************************************************************
 * GPS RIGHT
 * A part in the orbital simulator created when a GPS is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class GPSRight: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for GPS Right specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for GPS Right specific draw
   void draw() const { drawGPSRight(position, angularVelocity, Position()); }
};

/**********************************************************************
 * GPS LEFT
 * A part in the orbital simulator created when a GPS is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class GPSLeft: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for GPS Left specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for GPS Left specific draw
   void draw() const { drawGPSRight(position, angularVelocity, Position()); }
};

/**********************************************************************
 * HUBBLE SATELLITE
 * The hubble satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Hubble: public Satellite
{
public:
   // Constructor
   Hubble();
   
   // Must reimplement for hubble specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for hubble specific draw
   void draw() const { drawHubble(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE TELESCOPE
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class HubbleTelescope: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for hubble telescope specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for hubble telescope specific draw
   void draw() const { drawHubbleTelescope(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE COMPUTER
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class HubbleComputer: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for hubble computer specific destroy
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for hubble computer specific draw
   void draw() const { drawHubbleComputer(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE LEFT
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class HubbleLeft: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for hubble left specific destroy
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for hubble left specific draw
   void draw() const { drawHubbleLeft(position, angularVelocity); }
};

/**********************************************************************
 * HUBBLE RIGHT
 * A part in the orbital simulator created when HUBBLE  is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class HubbleRight: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for hubble right specific destroy
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for hubble right specific draw
   void draw() const { drawHubbleRight(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON SATELLITE
 * The sputnik satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Dragon: public Satellite
{
public:
   // Constructor
   Dragon();
   
   // Must reimplement for dragon specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for dragon specific draw
   void draw() const { drawCrewDragon(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON CENTER
 * A part in the orbital simulator created when DRAGON  is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class DragonCenter: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for dragon center specific destroy
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for dragon center specific draw
   void draw() const { drawCrewDragonCenter(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON RIGHT
 * A part in the orbital simulator created when DRAGON  is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class DragonRight: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for dragon right specific destroy
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for dragon right specific draw
   void draw() const { drawCrewDragonRight(position, angularVelocity); }
};

/**********************************************************************
 * DRAGON LEFT
 * A part in the orbital simulator created when DRAGON  is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class DragonLeft: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for dragon left specific destroy
   virtual void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for dragon left specific draw
   void draw() const { drawCrewDragonLeft(position, angularVelocity); }
};

/**********************************************************************
 * STARLINK SATELLITE
 * A starlink satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Starlink: public Satellite
{
public:
   // Constructor
   Starlink();
   
   // Must reimplement for starlink specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for starlink specific draw
   void draw() const { drawStarlink(position, angularVelocity); }
};

/**********************************************************************
 * STARLINK BODY
 * A part in the orbital simulator created when STARLINK is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class StarlinkBody: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for starlink body specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for starlink body specific draw
   void draw() const { drawStarlinkBody(position, angularVelocity); }
};

/**********************************************************************
 * STARLINK ARRAY
 * A part in the orbital simulator created when STARLINK is destroyed.
 * Inherits from SATELLITE
 **********************************************************************/
class StarlinkArray: public Satellite
{
public:
   using Satellite :: Satellite;    // for use of satellite parent constructor
   
   // Must reimplement for starlink array specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for starlink array specific draw
   void draw() const { drawStarlinkArray(position, angularVelocity); }
};

/**********************************************************************
 * SHIP SATELLITE
 * The ship satellite in the orbital simulator. Inherits from SATELLITE
 **********************************************************************/
class Ship: public Satellite
{
public:
   // Constructor
   Ship();
   
   // Must reimplement for ship specific input
   void input(const Interface* pUI, std::list<Satellite *> & satellites);
   
   // Must reimplement for ship specific destroy
   void destroy(std::list<Satellite *> & satellites) const;
   
   // Must reimplement for ship specific draw
   void draw() const { drawShip(position, angle.getRadian(), thrust); }
   
private:
   bool thrust;   // is the ship thrusting
};

/**********************************************************************
 * ATOMIC SATELLITE
 * An abstract base class for satellites that do not break into
 * more satellites and expire. Inherits from Satellite
 **********************************************************************/
class AtomicSatellite : public Satellite
{
public:
   
   // constructor
   using Satellite :: Satellite;
   
   // Must reimplement for atomic satellite specific destroy
   virtual void destroy(std::list<Satellite *> & satellites) const
   { /* Atomics do not break into more satellites */}
   
   // Must reimplement for atomic specific expire
   // check if the satellite has expired
   bool hasExpired() const { return  aliveTime >= lifeSpan; }
   
   // Must reimplement for atomic specific age
   // add seconds to the age of a satellite
   void age(double amountSeconds) { aliveTime += amountSeconds; }
   
protected:
   double lifeSpan;        // the life span of the satellite in frames
   double aliveTime;       // the age of the satellite in frames
};


/**********************************************************************
 * FRAGMENT
 * A fragment in the orbital simulator. Inherits from Atomic Satellite
 **********************************************************************/
class Fragment: public AtomicSatellite
{
public:
   // Constructor
   Fragment(const Satellite & parent, Angle shootOff);
   
   // Must reimplement for fragment specific draw
   void draw() const { drawFragment(position, angularVelocity); }
};

/**********************************************************************
 * PROJECTILLE
 * A projectille in the orbital simulator. Inherits from Expiring Satellite
 **********************************************************************/
class Projectile: public AtomicSatellite
{
public:
   // Constructor
   Projectile(const Ship & parent, Velocity bullet);
   
   // Must reimplement for projectile specific draw
   void draw() const { drawProjectile(position); }
};

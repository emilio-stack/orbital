/***********************************************************************
 * Header File:
 *    Satellite : A generic satellite in Earth's orbit
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    This is not any specific satellite. The main purpose of this
 *    class is to get the orbit working in the simulator
 ************************************************************************/

#pragma once

#include "position.h"
#include "velocity.h"
#include "explosion.h"

class Satellite
{
   
public:
   // Test class is a friend for private access
   friend class TestSatellite;
   
   // Constructor
   Satellite(): position(0, 42164000), initVelocityX(-3100.0), initVelocityY(0.0) {}
   
   // Accessors
   Position getPosition() const  { return position;      }
   Angle getAngle() const        { return angle;         }
   virtual bool checkExpired()   { return false;         }

   // Mutators
   void update();

   Angle rotateRight() { angle.addRadian(0.1); return angle; };
   Angle rotateLeft() { angle.addRadian(-0.1); return angle; };

   // accelerate ship
   void accelerate(bool canAccelerate);
   
protected:
   float expiresAfter;              // The expiration timer for the satellite
   float age;                       // The age of the satellite

public:
   Position position;               // The position of the satellite
   Velocity velocity;               // The velocity of the satellite
   Explosion explosions;
   Angle angle;                     // The angle in radians
   double initVelocityX;            // The initial horizontal velocity
   double initVelocityY;            // The initial vertical velocity
};

// The fragment class
class Fragment: public Satellite
{
public:
   bool checkExpired() { return age >= expiresAfter ? 1 : 0; }
};

// The projectille class
class Projectille: public Satellite
{
public:
   Projectille(){};
   bool checkExpired() { return age >= expiresAfter ? 1 : 0; }
};

// The sputnik class
class Sputnik: public Satellite
{
public:
   Sputnik(){};
};

// The dragon class
class Dragon: public Satellite
{
public:
   Dragon(){};
};

// The GPS class
class GPS: public Satellite
{
public:
   GPS(){};
};

// The Hubble class
class Hubble: public Satellite
{
public:
   Hubble(){};
};

// The Ship class
class Ship: public Satellite
{
public:
   Ship()
   {
      position.setMetersX(0);
      position.setMetersY(42164000.0);
      velocity.setDX(-3100);
      velocity.setDY(0);
   };
};

// The Atomic class
class Atomic: public Satellite
{
public:
   Atomic(){};
};

// The Starlink class
class Starlink: public Satellite
{
public:
   Starlink(){};
};

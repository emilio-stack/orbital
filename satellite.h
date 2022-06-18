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

class Satellite
{
   
public:
   // Test class is a friend for private access
   friend class TestSatellite;
   
   // Constructor
   Satellite(): position(0, 42164000) {}
   
   // Accessors
   Position getPosition() const { return position; }
   double getAngle() const { return currentAngle; }
   
   // Mutators
   void update();
   
private:
   Position position;               // The position of the satellite
   double currentAngle;             // The angle in radians
   double initVelocityX = -3100.0;  // The initial horizontal velocity
   double initVelocityY = 0.0;      // The initial vertical velocity
};

// The fragment class
class Fragment: public Satellite
{
public:
   Fragment(){};
};

// The projectille class
class Projectille: public Satellite
{
public:
   Projectille(){};
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
   Ship(){};
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

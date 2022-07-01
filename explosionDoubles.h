/***********************************************************************
 * Header File:
 *    Explosion Doubles : All of the doubles of the explosion class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    This file provides all the doubles of the explosion class.
 ************************************************************************/

#pragma once

#include "explosion.h"

/***********************************************************************
 * SPUTNIK EXPLOSION STUB
 * The stub double for the sputnik explosion
 ************************************************************************/
class SputnikExplosionStub : public Explosion
{
public:
   SputnikExplosionStub()
   { 
      setFragments(4.0);
      setParts(0.0);
   };
};

/***********************************************************************
 * DRAGON EXPLOSION STUB
 * The stub double for the dragon explosion
 ************************************************************************/
class DragonExplosionStub : public Explosion
{
public:
   DragonExplosionStub()
   {
      setFragments(2.0);
      setParts(3.0);
   };
};

/***********************************************************************
 * GPS EXPLOSION STUB
 * The stub double for the GPS explosion
 ************************************************************************/
class GPSExplosionStub : public Explosion
{
public:
   GPSExplosionStub()
   {
      setFragments(2.0);
      setParts(3.0);
   };
};

/***********************************************************************
 * HUBBLE EXPLOSION STUB
 * The stub double for the Hubble explosion
 ************************************************************************/
class HubbleExplosionStub : public Explosion
{
public:
   HubbleExplosionStub()
   {
      setFragments(0.0);
      setParts(4.0);
   };
};

/***********************************************************************
 * SHIP EXPLOSION STUB
 * The stub double for the ship explosion
 ************************************************************************/
class ShipExplosionStub : public Explosion
{
public:
   ShipExplosionStub()
   {
      setFragments(4.0);
      setParts(0.0);
   };
};

/***********************************************************************
 * ATOMIC EXPLOSION STUB
 * The stub double for the atomic explosion
 ************************************************************************/
class AtomicExplosionStub : public Explosion
{
public:
   AtomicExplosionStub()
   {
      setFragments(0.0);
      setParts(0.0);
   };
};

/***********************************************************************
 * PROJECTILLE EXPLOSION STUB
 * The stub double for the projectille explosion
 ************************************************************************/
class ProjectilleExplosionStub : public Explosion
{
public:
   ProjectilleExplosionStub()
   {
      setFragments(0.0);
      setParts(0.0);
   };
};

/***********************************************************************
 * STARLINK EXPLOSION STUB
 * The stub double for the projectille explosion
 ************************************************************************/
class StarlinkExplosionStub : public Explosion
{
public:
   StarlinkExplosionStub()
   {
      setFragments(2.0);
      setParts(2.0);
   };
};

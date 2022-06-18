/***********************************************************************
 * Header File:
 *    Velocity Doubles : All of the doubles of the velocity class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    This file provides all the doubles of the velocity class.
 ************************************************************************/

#pragma once

#include "velocity.h"      // For VELOCITY


/***********************************************************************
 * VELOCITY DUMMY
 * The double for the velocity class that verifies it is never used
 ************************************************************************/
class VelocityDummy: public Velocity
{
public:
   // constructor
   VelocityDummy(){};
};


/***********************************************************************
 * VELOCITY FAKE
 * The double for the Velocity class that always is initialized to
 * -3100, 0 and allows VelocityX and VelocityY to be set
 ************************************************************************/
class VelocityFake: public Velocity
{
public:
   // constructor
   VelocityFake(){};
};

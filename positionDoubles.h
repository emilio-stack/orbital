/***********************************************************************
 * Header File:
 *    Position Doubles : All of the doubles of the position class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    This file provides all the doubles of the position class.
 ************************************************************************/

#pragma once

#include "Position.h"      // For POSITION


/***********************************************************************
 * POSITION DUMMY
 * The double for the position class that verifies it is never used
 ************************************************************************/
class PositionDummy: public Position
{
public:
   // constructor
   PositionDummy() {};
};

/***********************************************************************
 * POSITION FAKE
 * The double for the position class that always is initialized to
 * 0, 42164000.0 and allows X and Y to be set
 ************************************************************************/
class PositionFake: public Position
{
public:
   // constructor
   PositionFake()
   {
      setMetersX(0.0);
      setMetersY(42164000.0);
   };
};


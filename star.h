/***********************************************************************
 * Source File:
 *    Star: represents a star in the simulator
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    Handles creating the stars within specified boundary points
 *    handles updating the star phase, handles drawing the star.
 ************************************************************************/

#pragma once

#include <cassert>
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for OGSTREAM

using namespace std;

/**************************************************
 * STAR
 * Keeps track of where the star is, and what its
 * phase is. Phase makes it twinkle.
 *************************************************/
class Star
{
public:
   // constructor
   Star();
   Star(const Position& ptBoundary);

   // drawers
   void draw();
    
private:
   Position position;
   unsigned char phase;
};

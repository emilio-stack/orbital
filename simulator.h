/***********************************************************************
 * Header File:
 *    Simulator : A class to run the orbit simulator
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    Provides a convenient interface to run the orbital simulator
 ************************************************************************/

#pragma once

#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
#include "earth.h"      // for EARTH
#include "star.h"       // for STAR
#include "satellite.h"  // for SATELLITE *
#include "constants.h"  // for CONSTANTS *
#include <list>         // for LIST

using namespace std;

/*************************************************************************
 * Simulator
 * A class to handle the orbital logic
 *************************************************************************/
class Simulator
{
public:
   Simulator(Position ptUpperRight);
   
   // handle simulator input, updates, and graphics
   void input(const Interface* pUI);
   void update();
   void draw();
   
private:
   Earth earth;                     // the earth
   list<Satellite *> satellites;    // collection of satellites in orbit
   Position ptUpperRight;           // size of the screen
   Star stars[NUM_STARS];           // the star array
};

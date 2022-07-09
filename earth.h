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

#include "Position.h"      // for POSITION
#include "constants.h"     // for CONSTANTS

class Earth
{
public:
   // constructors
   Earth(): position(0.0, 0.0), angle(0.0) {}
   
   // getters
   double getAngle() { return angle; }
   Position getPosition() { return position; }
   void draw() const { drawEarth(position, angle); }
   
   // modifers
   void update() { angle += -(2.0 * M_PI / 30.0) * (TIME_DILATION / 86400.0); }
   
private:
   Position position; // the position of the earth
   double angle;      // the angle of the earth in radians
};

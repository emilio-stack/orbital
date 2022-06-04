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
   
   // Constructor
   Satellite(): position(21082000.0, 36515095.0), angle(0.523599) {}
   
   // Accessors
   Position getPosition() const { return position; }
   double getAngle() const { return angle; }
   
   // Mutators
   void update();
   
private:
   Position position;   // The position of the satellite
   double angle;        // The angle in radians

};

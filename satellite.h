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
   Satellite(): position(21082000.0, 36515095.0), angle(0.523599) 
   {
      velocityX = -3100.0;
      velocityY = 0.0;
      altitude = 35786000;
      accelerationX = -0.1122;
      accelerationY = -0.1943;
      newX = 21082000;
      newY = 36515095;
      gravity = -0.2244;
   }
   
   // Accessors
   Position getPosition() const { return position; }
   double getAngle() const { return angle; }
   
   // Mutators
   void update();
   
private:
   Position position;   // The position of the satellite
   double angle;        // The angle in radians
   double velocityX;
   double velocityY;
   double altitude;
   double accelerationX;
   double accelerationY;
   double newX;
   double newY;
   double gravity;
};

/***********************************************************************
 * Header File:
 *    Angle : The angle class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    A class to represent an Angle in the orbital simulator
 ************************************************************************/

#pragma once

class Angle
{
public:
   // The test suite is a friend for private access
   friend class TestAngle;
   
   // The default constructor
   Angle(){};
   
   // Getters
   double getRadian();
   double getDegrees();
   
   // Setters
   void setRadian(double amount);
   void setDegrees(double amount);
   void addRadian(double amount);
   void addDegrees(double amount);
   
   
private:
   double angle;  // The angle stored in degrees
   
   // converters
   double degreesFromRadian(double radian);
   double radianFromDegrees(double degrees);
   double degreesFromXY(double x, double y);
   double normalize(double angle);
};

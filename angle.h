/***********************************************************************
 * Header File:
 *    Angle : The angle class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    A class to represent an Angle in the orbital simulator
 ************************************************************************/

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class Angle
{
public:
   // The test suite is a friend for private access
   friend class TestAngle;
   
   // Constructors
   Angle() : angle(0.0f) {};
   Angle(double angle) { setDegrees(normalize(angle)); }
   Angle(double x, double y) { angle =  degreesFromXY(x, y); }
   
   // Getters
   virtual double getRadian() const { return radianFromDegrees(angle); };
   virtual double getDegrees() const { return angle; };
   
   // Setters
   void setDegrees(double newAngleDegrees);
   void setRadian(double newAngleRadians) { setDegrees((degreesFromRadian(newAngleRadians))); };
   
   // Updaters
   void addDegrees(double amount) { setDegrees(normalize(angle + amount)); };
   void addRadian(double amount) { addDegrees(degreesFromRadian(amount)); };
   
   
private:
   double angle;  // The angle stored in degrees
   
   // converters
   double degreesFromRadian(double radian)  const { return radian * 180 / M_PI; };
   double radianFromDegrees(double degrees) const { return degrees * M_PI / 180; };
   double degreesFromXY(double x, double y) const { return degreesFromRadian(atan2(x, y)); }
   double normalize(double angle);
   bool closeEnough(double computedValue, double hardcodeValue) const;
};

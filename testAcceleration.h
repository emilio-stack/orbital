/***********************************************************************
 * Header File:
 *    Test Acceleration : The test suite for the acceleration class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    This file provides resilient robustness to the acceleration class
 ************************************************************************/

#pragma once

#include "acceleration.h"  // for ACCELERATION
using namespace std;

class TestAcceleration
{
public:
   void run()
   {
      cout << "Acceleration:  ";
      test_gravityOnSurface();
      test_gravity500k();
      test_gravity2000k();
      cout << endl;
   }
   
private:
   //
   // Acceleration test cases
   //
   
   // test that gravity on earth's surface is 9.806
   void test_gravityOnSurface()
   {
      // setup
      Angle ang(180);
      double magnitude = -9.8066;
      
      // exercise
      Acceleration accel(ang, magnitude);
      
      // verify
      assert(accel.closeEnough(accel.x, 0.0));
      assert(accel.closeEnough(accel.y, -9.806));
   }  // teardown
   
   // test that gravity 500K above earth's surface is -8.4
   void test_gravity500k()
   {
      // setup
      Angle ang(180);
      double magnitude = -8.43267;
      
      // exercise
      Acceleration accel(ang, magnitude);
      
      // verify
      assert(accel.x == -8.4);
      assert(accel.y == 0.0);
   }  // teardown
   
   // test that gravity 2000K above earth's surface is -5.7
   void test_gravity2000k()
   {
      // setup
      Angle ang(180);
      double magnitude = -5.6834;
      
      // exercise
      Acceleration accel(ang, magnitude);
      
      // verify
      assert(accel.x == -5.7);
      assert(accel.y == 0.0);
   }  // teardown
};

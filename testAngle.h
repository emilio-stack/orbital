/***********************************************************************
 * Header File:
 *    Test Angle : The test suite for the angle class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    This file provides resilient robustness to the angle class
 ************************************************************************/

#pragma once

#include "angle.h"         // for the ANGLE
#include <cassert>         // for ASSERT
#include <cmath>           // for M_PI
#include <iostream>

/********************************************************************
 * TEST ANGLE
 * A friend class for Angle which contains the Angle unit tests
 *********************************************************************/
class TestAngle
{
public:
   
   // The default constructor
   TestAngle(){};
   
   // A method to run the test cases
   void run()
   {
      std::cout << "Angle: ";
      test_getRadian();
      test_getDegrees();
      test_setRadian();
      test_setDegrees();
      test_degreesFromRadian();
      test_radianFromDegrees();
      test_degreesFromXY();
      test_normalize_negative();
      test_normalize_positive();
      test_addRadian_positive();
      test_addRadian_negative();
      test_addDegrees_positive();
      test_addDegrees_negative();
      test_operator_equals();
      std::cout << "Passed\n";
   }
   
private:
   // Test the get radians method
   void test_getRadian()
   {
      // Setup
      Angle angle;
      angle.angle = 90.0;
      double value = 0.0;
      
      // Exercise
      value = angle.getRadian();
      
      // Verify
      assert(value == (M_PI / 2));
      assert(angle.closeEnough(value, 1.570796));
   }  // Teardown
   
   // Test the get degrees method
   void test_getDegrees()
   {
      // Setup
      Angle angle;
      angle.angle = 90.0;
      double value = 0.0;
      
      // Exercise
      value = angle.getDegrees();
      
      // Verify
      assert(value == 90.0);
   }  // Teardown
   
   // Test the set radian method
   void test_setRadian()
   {
      // Setup
      Angle angle;
      angle.angle = 90.0;
      
      // Exercise
      angle.setRadian(M_PI);
      
      // Verify
      assert(angle.angle == 180.0);
   }  // Teardown
   
   // Test the set degrees method
   void test_setDegrees()
   {
      // Setup
      Angle angle;
      angle.angle = 30.0;
      
      // Exercise
      angle.setDegrees(90.0);
      
      // Verify
      assert(angle.angle == 90.0);
   }  // Teardown
   
   // Test conversion to degrees from radian
   void test_degreesFromRadian()
   {
      // Setup
      Angle angle;
      angle.angle = 0.0;
      double value = 0.0;
      
      // Exercise
      value = angle.degreesFromRadian(0.785398);
      
      // Verify
      assert(angle.angle == 0.0);               // this method should not affect state
      assert(angle.closeEnough(value, 45.0));   // this method should only calculate
                                                // from radian given as an argument.
                                                // Not from the state.
      
   }  // Teardown
   
   // Test conversion to radian from degrees
   void test_radianFromDegrees()
   {
      // Setup
      Angle angle;
      angle.angle = 0.0;
      double value = 0.0;
      
      // Exercise
      value = angle.radianFromDegrees(45.0);
      
      // Verify
      assert(angle.angle == 0.0);                  // this method should not affect state
      assert(angle.closeEnough(value, 0.785398));  // this method should only calculate from degrees
                                                   // given as an argument. Not from the state
      
   }  // Teardown
   
   // Test conversion to degrees from position
   void test_degreesFromXY()
   {
      // Setup
      Angle angle;
      angle.angle = 0.0;
      double x = 21082000.0;
      double y = 36515095;
      double value = 0.0;
      
      // Exercise
      value = angle.degreesFromXY(x, y);
      
      // Verify
      assert(angle.angle == 0.0);               // this method should not affect state
      assert(angle.closeEnough(value, 30.0));   // this method should only calculate from degrees
                                                // given as an argument. Not from the state
      
   }  // Teardown
   
   // Test normalization of an invalid negative angle
   void test_normalize_negative()
   {
      // Setup
      Angle angle;
      angle.angle = 0.0;
      double value = 0.0;
      
      // Exercise
      value = angle.normalize(-315);
      
      // Verify
      assert(angle.angle == 0.0);   // this method should not affect state
      assert(value == 45.0);        // this method should only normailze the angle given
                                    // as an argument. It should not write to state.
   }  // Teardown
   
   // Test normalization of an invalid positive angle
   void test_normalize_positive()
   {
      // Setup
      Angle angle;
      angle.angle = 0.0;
      double value = 0.0;
      
      // Exercise
      value = angle.normalize(405);
      
      // Verify
      assert(angle.angle == 0.0);   // this method should not affect state
      assert(value == 45.0);        // this method should only normailze the angle given
                                    // as an argument. It should not write to state.
   }  // Teardown
   
   // Test add radian positive
   void test_addRadian_positive()
   {
      // Setup
      Angle angle;
      angle.angle = 45.0;
      
      // Exercise
      angle.addRadian(0.785398);
      
      // Verify
      assert(angle.closeEnough(angle.angle, 90.0));
   }  // Teardown...
   
   // Test add radian positive
   void test_addRadian_negative()
   {
      // Setup
      Angle angle;
      angle.angle = 45.0;
      
      // Exercise
      angle.addRadian(-0.785398);
      
      // Verify
      assert(angle.closeEnough(angle.angle, 0.0));
   }  // Teardown...
   
   // Test add degrees positive
   void test_addDegrees_positive()
   {
      // Setup
      Angle angle;
      angle.angle = 45.0;
      
      // Exercise
      angle.addDegrees(45.0);
      
      // Verify
      assert(angle.angle == 90.0);
   }  // Teardown...
   
   // Test add degrees negative
   void test_addDegrees_negative()
   {
      // Setup
      Angle angle;
      angle.angle = 45.0;
      
      // Exercise
      angle.addDegrees(-45.0);
      
      // Verify
      assert(angle.angle == 0.0);
   }  // Teardown...
   
   // Test operator =
   void test_operator_equals()
   {
      // Setup
      Angle angle1;
      angle1.angle = 0.0;
      Angle angle2;
      angle2.angle = 180.0;
      
      // Exercise
      angle1 = angle2;
      
      // Verify
      assert(angle1.angle == 180.0);
      assert(angle2.angle == 180.0);
   }  // Teardown...
   
};

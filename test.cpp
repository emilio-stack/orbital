/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testAngle.h"
#include "testSatellite.h"

/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
   std::cout << "Begin Unit Tests:\n";
   std::cout << "Position Tests Start\n";
   TestPosition().run();
   std::cout << "Position Tests Passed\n";
   std::cout << "Angle Tests Start\n";
   TestAngle().run();
   std::cout << "Angle Tests Passed\n";
   std::cout << "Satellite Tests Start\n";
   TestSatellite().run();
   std::cout << "Satellite Tests Passed\n";
}

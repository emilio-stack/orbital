///***********************************************************************
// * Header File:
// *    Test Satellite : The test suite for the satellite class
// * Authors:
// *    Emilio Regino, Bradley Payne
// * Summary:
// *    This file provides resilient robustness to the satellite class
// ************************************************************************/
//
//
//#pragma once
//
//#include "satellite.h"        // for SATELLITE
//#include <cassert>            // for ASSERT
//#include <iostream>           // for COUT
//#include <vector>             // for VECTOR
//using namespace std;
//
//class TestSatellite
//{
//public:
//
//   // The default constructor
//   TestSatellite(){};
//
//   // A method to run the test cases
//   void run()
//   {
//      std::cout << "Satellite: ";
//      testFragment_checkExpired_false();
//      testFragment_checkExpired_true();
//      testProjectille_checkExpired_false();
//      testProjectille_checkExpired_true();
//      testSatellite_checkExpired_false();
//      testSatellite_computeAltitude();
//      testSatellite_computeGravity();
//      testSatellite_update();
//      testSatellite_updateSurface();
//      testSatellite_update500k();
//      testSatellite_update2000k();
//      testSputnik_explode();
//      testDragon_explode();
//      testGPS_explode();
//      testHubble_explode();
//      testShip_explode();
//      testAtomic_explode();
//      testProjectile_explode();
//      testStarlink_explode();
////      testShip_rotateRight();
////      testShip_rotateLeft();
////      testSatellite_rotateRight();
////      testSatellite_rotateLeft();
////      testShip_accelerate_true();
////      testShip_accelerate_false();
////      testSatellite_accelerate_true();
////      testSatellite_accelerate_false();
//      std::cout << "Passed\n";
//   }
//
//private:
//
//   // test the expired false case for the fragment satellite
//   void testFragment_checkExpired_false()
//   {
//      // Setup
//      GPS parent(Position(0.0, 0.0), Velocity(0.0, 0.0));
//      Angle angle(90.0);
//      Fragment sat(parent, angle);
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      sat.lifeSpan = 5.0;
//      sat.aliveTime = 4.0;
//      bool value;
//
//      // Exercise
//      value = sat.hasExpired();
//
//      // Verify
//      assert(value == false);
//      assert(sat.lifeSpan == 5.0);
//      assert(sat.aliveTime == 4.0);
////      assert(sat.position.getMetersX() == 0.0);
////      assert(sat.velocity.getY() == 0.0);
//   }  // Teardown
//
//   // test the expired true case for the fragment satellite
//   void testFragment_checkExpired_true()
//   {
//      // Setup
//      GPS parent(Position(0.0, 0.0), Velocity(0.0, 0.0));
//      Angle angle(90.0);
//      Fragment sat(parent, angle);
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      sat.lifeSpan = 5.0;
//      sat.aliveTime = 5.0;
//      bool value;
//
//      // Exercise
//      value = sat.hasExpired();
//
//      // Verify
//      assert(value == true);
//      assert(sat.lifeSpan == 5.0);
//      assert(sat.aliveTime == 5.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the expired false case for the projectille satellite
//   void testProjectille_checkExpired_false()
//   {
//      // Setup
//      Ship parent;
//      Velocity v;
//      Projectile sat(parent, v);
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      sat.lifeSpan = 5.0;
//      sat.aliveTime = 4.0;
//      bool value;
//
//      // Exercise
//      value = sat.hasExpired();
//
//      // Verify
//      assert(value == false);
//      assert(sat.lifeSpan == 5.0);
//      assert(sat.aliveTime == 4.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the expired true case for the projectille satellite
//   void testProjectille_checkExpired_true()
//   {
//      // Setup
//      Ship parent;
//      Velocity v;
//      Projectile sat(parent, v);
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      sat.lifeSpan = 5.0;
//      sat.aliveTime = 5.0;
//      bool value;
//
//      // Exercise
//      value = sat.hasExpired();
//
//      // Verify
//      assert(value == true);
//      assert(sat.lifeSpan == 5.0);
//      assert(sat.aliveTime == 5.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the expired false case for the satellite class
//   void testSatellite_checkExpired_false()
//   {
//      // Setup
//      GPS sat; // Satellite is abstract so we will use a dervied class to test
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      bool value;
//
//      // Exercise
//      value = sat.hasExpired();
//
//      // Verify
//      assert(value == false);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the satellite compute altitude method
//   void testSatellite_computeAltitude()
//   {
//      // Setup
//      GPS sat;          // Satellite is abstract so we will use a dervied class to test
//      Position p(21082000.0, 36515095);
//      sat.position = p;
//      double value;
//
//      // Exercise
//      value = sat.computeAltitude();
//
//      // Verify
//      assert(sat.closeEnough(value, 35785999.8916));
//   }  // Teardown
//
//   // test the satellite compute gravity method
//   void testSatellite_computeGravity()
//   {
//      // Setup
//      Starlink sat;     // Satellite is abstract so we will use a dervied class to test
//      Position p(21082000.0, 36515095);
//      sat.position = p;
//      double value;
//
//      // Exercise
//      value = sat.computeGravity();
//
//      // Verify
//      assert(sat.closeEnough(value, -0.2244));
//   }  // Teardown
//
//   // test the satellite update method
//   void testSatellite_update()
//   {
//      // Setup
//      Hubble sat;          // Satellite is abstract so we will use a dervied class to test
//      Position p(21082000.0, 36515095);
//      Velocity v(-2685.0, 1550.0);
//      Angle a(30.0);
//      sat.position = p;
//      sat.velocity = v;
//      sat.angle = a;
//      double time = 48.0;
//
//      // Exercise
//      sat.update(time);
//
//      // Verify
//      assert(sat.closeEnough(sat.position.getMetersX(),  20952732.2517));
//      assert(sat.closeEnough(sat.position.getMetersY(),  36588823.4003));
//      assert(sat.closeEnough(sat.velocity.getX(),        -2690.3853));
//      assert(sat.closeEnough(sat.velocity.getY(),        1540.6722));
//   }  // Teardown
//
//   // test the satellite update method on the surface of the earth
//   void testSatellite_updateSurface()
//   {
//      // Setup
//      Hubble sat;          // Satellite is abstract so we will use a dervied class to test
//      Position p(6378000.0, 0.0);
//      Velocity v(0.0, 0.0);
//      sat.position = p;
//      sat.velocity = v;
//      double time = 48.0;
//
//      // Exercise
//      sat.update(time);
//
//      // Verify
////      assert(sat.closeEnough(sat.position.getMetersX(),  20952732.2517));
////      assert(sat.closeEnough(sat.position.getMetersY(),  36588823.4003));
////      assert(sat.closeEnough(sat.velocity.getX(),        -2690.3853));
////      assert(sat.closeEnough(sat.velocity.getY(),        1540.6722));
//   }  // Teardown
//
//   // test the satellite update method 500k meters above the surface of the earth
//   void testSatellite_update500k()
//   {
//      // Setup
//      Hubble sat;          // Satellite is abstract so we will use a dervied class to test
//      Position p(6378000.0 + 500000.0, 0.0);
//      Velocity v(0.0, 0.0);
//      sat.position = p;
//      sat.velocity = v;
//      double time = 48.0;
//
//      // Exercise
//      sat.update(time);
//
//      // Verify
////      assert(sat.closeEnough(sat.position.getMetersX(),  20952732.2517));
////      assert(sat.closeEnough(sat.position.getMetersY(),  36588823.4003));
////      assert(sat.closeEnough(sat.velocity.getX(),        -2690.3853));
////      assert(sat.closeEnough(sat.velocity.getY(),        1540.6722));
//   }  // Teardown
//
//   // test the satellite update method 2000k meters above the surface of the earth
//   void testSatellite_update2000k()
//   {
//      // Setup
//      Hubble sat;          // Satellite is abstract so we will use a dervied class to test
//      Position p(6378000.0 + 2000000.0, 0.0);
//      Velocity v(0.0, 0.0);
//      sat.position = p;
//      sat.velocity = v;
//      double time = 48.0;
//
//      // Exercise
//      sat.update(time);
//
//      // Verify
////      assert(sat.closeEnough(sat.position.getMetersX(),  20952732.2517));
////      assert(sat.closeEnough(sat.position.getMetersY(),  36588823.4003));
////      assert(sat.closeEnough(sat.velocity.getX(),        -2690.3853));
////      assert(sat.closeEnough(sat.velocity.getY(),        1540.6722));
//   }  // Teardown
//
//   // test the explosion from sputnik
//   void testSputnik_explode()
//   {
//      // Setup
//      Sputnik sat;
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
////      cout << endl;
////      for (int i = 0; i < satellites.size(); ++i)
////      {
////         cout << "Satellite "<< i << " type: " << typeid(satellites[i]).name() << endl;
////      }
//      assert(satellites.size() == 4);
////      assert(explosion.getFragments == 4.0);
////      assert(explosion.getParts == 0.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the explosion from dragon
//   void testDragon_explode()
//   {
//      // Setup
//      Dragon sat;
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
//      assert(satellites.size() == 5);
////      assert(explosion.getFragments == 2.0);
////      assert(explosion.getParts == 3.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the explosion from GPS
//   void testGPS_explode()
//   {
//      // Setup
//      GPS sat;
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
//      assert(satellites.size() == 5);
////      assert(explosion.getParts == 3.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the explosion from Hubble
//   void testHubble_explode()
//   {
//      // Setup
//      Hubble sat;
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
//      assert(satellites.size() == 4);
////      assert(explosion.getParts == 4.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the explosion from Ship
//   void testShip_explode()
//   {
//      // Setup
//      Ship sat;
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
//      assert(satellites.size() == 3);
////      assert(explosion.getParts == 0.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the explosion from Atomic
//   void testAtomic_explode()
//   {
//      // Setup
//      Fragment sat;        // ATOMIC SATELLITE is abstract so we will use a derived class to test
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
//      assert(satellites.size() == 0);
////      assert(explosion.getParts == 0.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the explosion from Projectille
//   void testProjectile_explode()
//   {
//      // Setup
//      Projectile sat;
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
//      assert(satellites.size() == 0);
////      assert(explosion.getParts == 0.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
//   // test the explosion from Star link
//   void testStarlink_explode()
//   {
//      // Setup
//      Starlink sat;
//      Position pd;
//      Velocity vd;
//      sat.position = pd;
//      sat.velocity = vd;
//      vector<Satellite*> satellites;
//
//      // Exercise
//      sat.destroy(satellites);
//
//      // Verify
//      assert(satellites.size() == 4);
////      assert(explosion.getParts == 2.0);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
//   }  // Teardown
//
////   // test the ship rotation right case
////   void testShip_rotateRight()
////   {
////      // Setup
////      Ship sat;
////      Position pd;
////      Velocity vd;
////      Angle a (45);
////      sat.position = pd;
////      sat.velocity = vd;
////      sat.angle = a;
////
////      // Exercise
////      sat.rotateRight();
////
////      // Verify
////      assert(sat.angle.getRadian() == 0.885398);
//////      assert(sat.position == PositionDummy());
//////      assert(sat.velocity == VelocityDummy());
////   }  // Teardown
////
////   // test the ship rotation left case
////   void testShip_rotateLeft()
////   {
////      // Setup
////      Ship sat;
////      sat.position = PositionDummy();
////      sat.velocity = VelocityDummy();
////      sat.angle = AngleStub();      // 45 degrees
////
////      // Exercise
////      sat.rotateLeft();
////
////      // Verify
////      assert(sat.angle.getRadian() == 0.685398);
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
////   }  // Teardown
////
////   // test the satellite rotation right case
////   void testSatellite_rotateRight()
////   {
////      // Setup
////      Satellite sat;
////      sat.position = PositionDummy();
////      sat.velocity = VelocityDummy();
////
////      // Exercise
////      sat.rotateRight();
////
////      // Verify
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
////   }  // Teardown
////
////   // test the satellite rotation left case
////   void testSatellite_rotateLeft()
////   {
////      // Setup
////      Satellite sat;
////      sat.position = PositionDummy();
////      sat.velocity = VelocityDummy();
////
////      // Exercise
////      sat.rotateLeft();
////
////      // Verify
////      assert(sat.position == PositionDummy());
////      assert(sat.velocity == VelocityDummy());
////   }  // Teardown
////
////   // test the ship accelerate true case
////   void testShip_accelerate_true()
////   {
////      // Setup
////      Ship sat;
////      sat.position = PositionFake();
////      sat.velocity = VelocityFake();
////      sat.angle = AngleStub();      // 45 degrees
////
////      // Exercise
////      sat.accelerate(true);
////
////      // Verify
////      assert(sat.position.getMetersX() == -148800.0);
////      assert(sat.position.getMetersY() == 42162707.50587);
////      assert(sat.velocity.getVelocityX() == -3100.0);
////      assert(sat.velocity.getVelocityY() == -21.5415688);
////   }  // Teardown
////
////   // test the ship accelerate false case
////   void testShip_accelerate_false()
////   {
////      // Setup
////      Ship sat;
////      sat.position = PositionFake();
////      sat.velocity = VelocityFake();
////      sat.angle = AngleStub();      // 45 degrees
////
////      // Exercise
////      sat.accelerate(false);
////
////      // Verify
////      assert(sat.position.getMetersX() == -148800.0);
////      assert(sat.position.getMetersY() == 42163224.503522);
////      assert(sat.velocity.getVelocityX() == -3100.0);
////      assert(sat.velocity.getVelocityY() == -10.77078442);
////   }  // Teardown
////
////   // test the satellite accelerate true case
////   void testSatellite_accelerate_true()
////   {
////      // Setup
////      Satellite sat;
////      sat.position = PositionFake();
////      sat.velocity = VelocityFake();
////      sat.angle = AngleStub();      // 45 degrees
////
////      // Exercise
////      sat.accelerate(true);
////
////      // Verify
////      assert(sat.position.getMetersX() == -148800.0);
////      assert(sat.position.getMetersY() == 42163224.503522);
////      assert(sat.velocity.getVelocityX() == -3100.0);
////      assert(sat.velocity.getVelocityY() == -10.77078442);
////   }  // Teardown
////
////   // test the satellite accelerate false case
////   void testSatellite_accelerate_false()
////   {
////      // Setup
////      Satellite sat;
////      sat.position = PositionFake();
////      sat.velocity = VelocityFake();
////      sat.angle = AngleStub();      // 45 degrees
////
////      // Exercise
////      sat.accelerate(false);
////
////      // Verify
////      assert(sat.position.getMetersX() == -148800.0);
////      assert(sat.position.getMetersY() == 42163224.503522);
////      assert(sat.velocity.getVelocityX() == -3100.0);
////      assert(sat.velocity.getVelocityY() == -10.77078442);
////   }  // Teardown
//};

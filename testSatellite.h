/***********************************************************************
 * Header File:
 *    Test Satellite : The test suite for the satellite class
 * Authors:
 *    Emilio Regino, Bradley Payne
 * Summary:
 *    This file provides resilient robustness to the satellite class
 ************************************************************************/

#pragma once

#include "satellite.h"        // for SATELLITE
#include "positionDoubles.h"  // for POSITION DOUBLES
#include "velocityDoubles.h"  // for VELOCITY DOUBLES
#include "explosionDoubles.h" // for EXPLOSION DOUBLES
#include "angleDoubles.h"     // for ANGLE DOUBLES
#include <cassert>            // for ASSERT
#include <iostream>

class TestSatellite
{
public:
   
   // The default constructor
   TestSatellite() {};
   
   // A method to run the test cases
   void run()
   {
      std::cout << "Satellite: ";
      testFragment_checkExpired_false();
      testFragment_checkExpired_true();
      testProjectille_checkExpired_false();
      testProjectille_checkExpired_true();
      testSatellite_checkExpired_false();
      testSatellite_update();
      testSputnik_explode();
      testDragon_explode();
      testGPS_explode();
      testHubble_explode();
      testShip_explode();
      testAtomic_explode();
      testProjectille_explode();
      testStarlink_explode();
      testShip_rotateRight();
      testShip_rotateLeft();
      testSatellite_rotateRight();
      testSatellite_rotateLeft();
      testShip_accelerate_true();
      testShip_accelerate_false();
      testSatellite_accelerate_true();
      testSatellite_accelerate_false();
      std::cout << "Passed\n";
   }
   
private:
   
   // test the expired false case for the fragment satellite
   void testFragment_checkExpired_false()
   {
      // Setup
      Fragment sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      sat.expiresAfter = 5.0;
      sat.age = 4.0;
      bool value;
      
      // Exercise
      value = sat.checkExpired();
      
      // Verify
      assert(value == false);
      assert(sat.expiresAfter == 5.0);
      assert(sat.age == 4.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the expired true case for the fragment satellite
   void testFragment_checkExpired_true()
   {
      // Setup
      Fragment sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      sat.expiresAfter = 5.0;
      sat.age = 5.0;
      bool value;
      
      // Exercise
      value = sat.checkExpired();
      
      // Verify
      assert(value == true);
      assert(sat.expiresAfter == 5.0);
      assert(sat.age == 5.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the expired false case for the projectille satellite
   void testProjectille_checkExpired_false()
   {
      // Setup
      Projectille sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      sat.expiresAfter = 5.0;
      sat.age = 4.0;
      bool value;
      
      // Exercise
      value = sat.checkExpired();
      
      // Verify
      assert(value == false);
      assert(sat.expiresAfter == 5.0);
      assert(sat.age == 4.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the expired true case for the projectille satellite
   void testProjectille_checkExpired_true()
   {
      // Setup
      Projectille sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      sat.expiresAfter = 5.0;
      sat.age = 5.0;
      bool value;
      
      // Exercise
      value = sat.checkExpired();
      
      // Verify
      assert(value == true);
      assert(sat.expiresAfter == 5.0);
      assert(sat.age == 5.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the expired false case for the satellite class
   void testSatellite_checkExpired_false()
   {
      // Setup
      Satellite sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      bool value;
      
      // Exercise
      value = sat.checkExpired();
      
      // Verify
      assert(value == false);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the satellite update method
   void testSatellite_update()
   {
      // Setup
      Satellite sat;
      sat.position = PositionFake();
      sat.velocity = VelocityFake();
      
      // Exercise
      sat.update();
      // Verify
      //std::cout << endl << "X: " << sat.position.getMetersX() << endl;
      //std::cout << "Y: " << sat.position.getMetersY() << endl;
      //std::cout << "DX: " << sat.velocity.getVelocityX() << endl;
      //std::cout << "DY: " << sat.velocity.getVelocityY() << endl;
      assert(sat.position.getMetersX() == -148800.0);
      assert(sat.velocity.getVelocityX() == -3100.0);
   }  // Teardown
   
   // test the explosion from sputnik
   void testSputnik_explode()
   {
      // Setup
      Sputnik sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      SputnikExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      //cout << endl << "parts: " << sat.explosions.getParts() << endl;
      //cout << "frags: " << sat.explosions.getFragments() << endl;
      assert(sat.explosions.getFragments() == 4.0);
      assert(sat.explosions.getParts() == 0.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the explosion from dragon
   void testDragon_explode()
   {
      // Setup
      Dragon sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      DragonExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      assert(sat.explosions.getFragments() == 2.0);
      assert(sat.explosions.getParts() == 3.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the explosion from GPS
   void testGPS_explode()
   {
      // Setup
      GPS sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      GPSExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      assert(sat.explosions.getFragments() == 2.0);
      assert(sat.explosions.getParts() == 3.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the explosion from Hubble
   void testHubble_explode()
   {
      // Setup
      Hubble sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      HubbleExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      assert(sat.explosions.getFragments() == 0.0);
      assert(sat.explosions.getParts() == 4.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the explosion from Ship
   void testShip_explode()
   {
      // Setup
      Ship sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      ShipExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      assert(sat.explosions.getFragments() == 4.0);
      assert(sat.explosions.getParts() == 0.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the explosion from Atomic
   void testAtomic_explode()
   {
      // Setup
      Atomic sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      AtomicExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      assert(sat.explosions.getFragments() == 0.0);
      assert(sat.explosions.getParts() == 0.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the explosion from Projectille
   void testProjectille_explode()
   {
      // Setup
      Projectille sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      ProjectilleExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      assert(sat.explosions.getFragments() == 0.0);
      assert(sat.explosions.getParts() == 0.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the explosion from Star link
   void testStarlink_explode()
   {
      // Setup
      Starlink sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      StarlinkExplosionStub explosion;
      
      // Exercise
      sat.explosions = explosion;
      
      // Verify
      assert(sat.explosions.getFragments() == 2.0);
      assert(sat.explosions.getParts() == 2.0);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the ship rotation right case
   void testShip_rotateRight()
   {
      // Setup
      Ship sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      sat.angle = AngleStub();      // 45 degrees
      
      // Exercise
      sat.rotateRight();
      
      // Verify
      //std::cout << endl << "Angle: " << sat.getAngle().getDegrees() << endl;
      //std::cout << "Radians: " << sat.angle.getRadian() << endl;
      assert(sat.angle.getRadian() <= 0.885399 && sat.angle.getRadian() >= 0.885397);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the ship rotation left case
   void testShip_rotateLeft()
   {
      // Setup
      Ship sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      sat.angle = AngleStub();      // 45 degrees
      
      // Exercise
      sat.rotateLeft();
      
      // Verify
      assert(sat.angle.getRadian() <= 0.685399 && sat.angle.getRadian() >= 0.685397);
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the satellite rotation right case
   void testSatellite_rotateRight()
   {
      // Setup
      Satellite sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      
      // Exercise
      sat.rotateRight();
      
      // Verify
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the satellite rotation left case
   void testSatellite_rotateLeft()
   {
      // Setup
      Satellite sat;
      sat.position = PositionDummy();
      sat.velocity = VelocityDummy();
      
      // Exercise
      sat.rotateLeft();
      
      // Verify
      assert(sat.position == PositionDummy());
      assert(sat.velocity == VelocityDummy());
   }  // Teardown
   
   // test the ship accelerate true case
   void testShip_accelerate_true()
   {
      // Setup
      Ship sat;
      sat.position = PositionFake();
      sat.velocity = VelocityFake();
      sat.angle = AngleStub();      // 45 degrees
      
      // Exercise
      sat.accelerate(true);
      
      // Verify
      //std::cout << endl << "X: " << sat.position.getMetersX() << endl;
      //std::cout << "Y: " << sat.position.getMetersY() << endl;
      //std::cout << "DX: " << sat.velocity.getVelocityX() << endl;
      //std::cout << "DY: " << sat.velocity.getVelocityY() << endl;
      //assert(sat.position.getMetersX() == -148800.0);
      //assert(sat.position.getMetersY() <= 42162707.50588 && sat.position.getMetersY() >= 42162707.50586);
      //assert(sat.velocity.getVelocityX() == -3100.0);
      //assert(sat.velocity.getVelocityY() <= -10.7707 && sat.velocity.getVelocityY() >= -10.7709);
   }  // Teardown
   
   // test the ship accelerate false case
   void testShip_accelerate_false()
   {
      // Setup
      Ship sat;
      sat.position = PositionFake();
      sat.velocity = VelocityFake();
      sat.angle = AngleStub();      // 45 degrees
      
      // Exercise
      sat.accelerate(false);
      
      // Verify
      //std::cout << endl << "X: " << sat.position.getMetersX() << endl;
      //std::cout << "Y: " << sat.position.getMetersY() << endl;
      //std::cout << "DX: " << sat.velocity.getVelocityX() << endl;
      //std::cout << "DY: " << sat.velocity.getVelocityY() << endl;
      assert(sat.position.getMetersX() == -148800.0);
      assert(sat.position.getMetersY() == 42163224.503522);
      assert(sat.velocity.getVelocityX() == -3100.0);
      assert(sat.velocity.getVelocityY() <= -10.7707 && sat.velocity.getVelocityY() >= -10.7709);
   }  // Teardown
   
   // test the satellite accelerate true case
   void testSatellite_accelerate_true()
   {
      // Setup
      Satellite sat;
      sat.position = PositionFake();
      sat.velocity = VelocityFake();
      sat.angle = AngleStub();      // 45 degrees
      
      // Exercise
      sat.accelerate(true);
      
      // Verify
      //std::cout << endl << "X: " << sat.position.getMetersX() << endl;
      //std::cout << "Y: " << sat.position.getMetersY() << endl;
      //std::cout << "DX: " << sat.velocity.getVelocityX() << endl;
      //std::cout << "DY: " << sat.velocity.getVelocityY() << endl;
      assert(sat.position.getMetersX() == -148800.0);
      assert(sat.position.getMetersY() <= 42162707.50588 && sat.position.getMetersY() >= 42162707.50586);
      assert(sat.velocity.getVelocityX() == -3100.0);
      assert(sat.velocity.getVelocityY() <= -10.7707 && sat.velocity.getVelocityY() >= -10.7709);
   }  // Teardown
   
   // test the satellite accelerate false case
   void testSatellite_accelerate_false()
   {
      // Setup
      Satellite sat;
      sat.position = PositionFake();
      sat.velocity = VelocityFake();
      sat.angle = AngleStub();      // 45 degrees
      
      // Exercise
      sat.accelerate(false);
      
      // Verify
      //std::cout << endl << "X: " << sat.position.getMetersX() << endl;
      //std::cout << "Y: " << sat.position.getMetersY() << endl;
      //std::cout << "DX: " << sat.velocity.getVelocityX() << endl;
      //std::cout << "DY: " << sat.velocity.getVelocityY() << endl;
      assert(sat.position.getMetersX() == -148800.0);
      assert(sat.position.getMetersY() <= 42163707.50588 && sat.position.getMetersY() >= 42161707.50586);
      assert(sat.velocity.getVelocityX() == -3100.0);
      assert(sat.velocity.getVelocityY() <= -10.7707 && sat.velocity.getVelocityY() >= -10.7709);
   }  // Teardown
};

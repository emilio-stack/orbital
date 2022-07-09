/***********************************************************************
 * Header File:
 *    Simulator : A class to run the orbit simulator
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    Provides a convenient interface to run the orbital simulator
 ************************************************************************/

#include "simulator.h"     // for SIMULATOR

/***********************************************************************
 * CONSTRUCTOR
 * Initializes all the member variables of the orbital
 * simulator: Stars, Satellites, ptUpperRight
 ************************************************************************/
Simulator::Simulator(Position ptUpperRight) :
ptUpperRight(ptUpperRight)
{
   // initialize the stars
   for (int i = 0; i < NUM_STARS; i++)
   {
      stars[i] = Star(ptUpperRight);
   }
   
   // initialize all the satellites
   Satellite * ship = new Ship;
   Satellite * sputnik = new Sputnik;
   Satellite * gps1 = new GPS (Position(0.0, 26560000.0), Velocity(-3880.0, 0.0));
   Satellite * gps2 = new GPS (Position(23001634.72, 13280000.0), Velocity(-1940.00, 3360.18));
   Satellite * gps3 = new GPS (Position(23001634.72, -13280000.0), Velocity(1940.00, 3360.18));
   Satellite * gps4 = new GPS (Position(0.0, -26560000.0), Velocity(0.0, -26560000.0));
   Satellite * gps5 = new GPS (Position(23001634.72, -13280000.0), Velocity(1940.00, -3360.18));
   Satellite * gps6 = new GPS (Position(-23001634.72, 13280000.0), Velocity( -1940.00, -3360.18));
   Satellite * hubble = new Hubble;
   Satellite * dragon = new Dragon;
   Satellite * starlink = new Starlink;

   // add them to the satellites collection
   satellites.push_back(ship);
   satellites.push_back(sputnik);
   satellites.push_back(hubble);
   satellites.push_back(dragon);
   satellites.push_back(starlink);
   satellites.push_back(gps1);
   satellites.push_back(gps2);
   satellites.push_back(gps3);
   satellites.push_back(gps4);
   satellites.push_back(gps5);
   satellites.push_back(gps6);
}

/*************************************************************************
 * INPUT
 * Handles all the input of the simulator
 *************************************************************************/
void Simulator::input(const Interface* pUI)
{
   // only the ship handles input
   // ship should be the first element
   satellites[0]->input(pUI, satellites);
}

/*************************************************************************
 * UPDATE
 * Updates all the satellites of the simulator
 *************************************************************************/
void Simulator::update()
{
   // update the earth
   earth.update();
   
   // update all satellites
   for (int i = 0; i < satellites.size(); i++)
   {
      satellites[i]->update(TIME_PER_FRAME);
   }
   
   // kill satellites that have collided
   for (int i = 0; i < satellites.size(); i++)
   {
      for (int j = i + 1; j < satellites.size(); j++)
      {
         if (!satellites[i]->isDead() and !satellites[j]->isDead())
         {
            double distance = computeDistance(satellites[i]->getPosition(),
                                              satellites[j]->getPosition());
            if (distance < satellites[i]->getRadius() + satellites[j]->getRadius())
            {
               satellites[j]->kill();
               satellites[j]->kill();
            }
         }
      }
   }
   
   // Remove dead satellites
   for (int i = 0; i < satellites.size(); i++)
   {
      if (satellites[i]->isDead())
      {
         satellites[i]->destroy(satellites);
         satellites.erase(satellites.begin() + i);
      }
   }
}

/*************************************************************************
 * DRAW
 * Draws all the satellites in the simulator to the screen
 *************************************************************************/
void Simulator::draw()
{
   // first draw the stars
   for (int currentStar = 0; currentStar < NUM_STARS; currentStar++)
      stars[currentStar].draw();

   // then the earth
   earth.draw();

   // then the satellites
   for (int i = 0; i < satellites.size(); i++)
      satellites[i]->draw();
}

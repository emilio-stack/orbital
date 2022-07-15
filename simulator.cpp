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
Simulator::Simulator(Position ptUpperRight)
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
   Satellite * gps4 = new GPS (Position(0.0, -26560000.0), Velocity(3880.0, 0.0));  
   Satellite * gps5 = new GPS (Position(-23001634.72, -13280000.0), Velocity(1940.00, -3360.18));
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
   list<Satellite *>::iterator it;
   for (it = satellites.begin(); it != satellites.end(); it++)
      (*it)->input(pUI, satellites);
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
   for (auto satellite: satellites)
      satellite->update(TIME_PER_FRAME);
   
   // kill satellites that have collided
   list<Satellite *>::iterator it1;
   list<Satellite *>::iterator it2;
   for (it1 = satellites.begin(); it1 != satellites.end(); ++it1)
   {
      it2 = it1;
      for (it2++; it2 != satellites.end(); ++it2)
      {
         // only check for collisions if not dead and not expired
         if (!(*it1)->isDead() && !(*it2)->isDead() &&
             !(*it1)->hasExpired() && !(*it2)->hasExpired())
         {
            
            // better not be checking myself
            assert(it1 != it2);
            
            // check for collision with other satellites
            double distance = computeDistance((*it1)->getPosition(),(*it2)->getPosition());
            if (distance < (*it1)->getRadius() + (*it2)->getRadius())
            {
               (*it1)->kill();
               (*it2)->kill();
            }
            
            // check for collision with earth for itr1
            distance = computeDistance((*it1)->getPosition(), earth.getPosition());
            if (distance < earth.getRadius())
               (*it1)->kill();
            
            // check for collision with earth for itr2
            distance = computeDistance((*it1)->getPosition(), earth.getPosition());
            if (distance < earth.getRadius())
               (*it2)->kill();
         }
      }
   }
   
   for (it1 = satellites.begin(); it1 != satellites.end(); )
   {
      // Remove dead satellites
      if ((*it1)->isDead())
      {
         (*it1)->destroy(satellites);
         it1 = satellites.erase(it1);
      }
      // Remove expired satellites
      else if ((*it1)->hasExpired())
         it1 = satellites.erase(it1);
      else
         ++it1;
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
   list<Satellite *>::iterator it;
   for (it = satellites.begin(); it != satellites.end(); it++)
      (*it)->draw();
}

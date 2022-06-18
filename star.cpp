/***********************************************************************
 * Source File:
 *    Star: represents a star in the simulator
 * Author:
 *    Emilio Regino
 * Summary:
 *    Handles creating the stars within specified boundary points
 *    handles updating the star phase, handles drawing the star.
 ************************************************************************/

#include "star.h"      // for the Star class definition

///******************************************************************
// * RANDOM
// * This function generates a random number.
// *
// *    INPUT:   min, max : The number of values (min <= num <= max)
// *    OUTPUT   <return> : Return the integer
// ****************************************************************/
//int random(int min, int max)
//{
//   assert(min < max);
//   int num = (rand() % (max - min)) + min;
//   assert(min <= num && num <= max);
//
//   return num;
//}
//
///******************************************************************
// * RANDOM
// * This function generates a random number.
// *
// *    INPUT:   min, max : The number of values (min <= num <= max)
// *    OUTPUT   <return> : Return the double
// ****************************************************************/
//double random(double min, double max)
//{
//   assert(min <= max);
//   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
//
//   assert(min <= num && num <= max);
//
//   return num;
//}


/*************************************************************************
 * STAR
 * The default constructor for the star class.
 * Position x is set to 0.0.
 * Posiition y is set to 0.0.
 * Phase is set to 0.
 *************************************************************************/
Star :: Star()
{
   position.setMetersX(0.0);
   position.setMetersY(0.0);
   phase = 0;
}

/*************************************************************************
 * STAR(PTBOUNDARY)
 * The preferred constructor for the star class.
 * Position x is set to randomized coordinate between 0 and the
 * specified boundry x.
 * min and max height are set to be a percent of the max height of
 * the screen.
 * Posiition y is set to randomized coordinate between min height
 * and max height.
 *************************************************************************/
Star :: Star(const Position& ptBoundary)
{
//   int maxHeight = ptBoundary.getMetersY() * 0.95;   // The max height a star can have is 95% of the height of the screen
//   int minHeight = ptBoundary.getMetersY() * 0.50;   // The min height a star can have is 50% of the height of the screen
   
   position.setMetersX(random(-ptBoundary.getMetersX(), ptBoundary.getMetersX()));
   position.setMetersY(random(-ptBoundary.getMetersY(), ptBoundary.getMetersY()));
   
   std::cout << "X: " << position.getPixelsX() << std::endl;
   std::cout << "Y: " << position.getPixelsY() << std::endl;
   
   
//   position.setMeters(21082000.0, 36515095.0);
//   position.setPixelsX(60);
//   position.setPixelsY(60);
   
   
   phase = random(0, 255);
}

/*************************************************************************
 * DRAW
 * A method to draw the star
 *************************************************************************/
void Star :: draw()
{
   drawStar(position, phase++);
}

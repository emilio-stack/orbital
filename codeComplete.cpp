/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"   // for POINT
#include "test.h"       // for TEST RUNNER
#include "earth.h"      // for EARTH
#include "star.h"       // for STAR
#include "satellite.h"  // for SATELLITE *
#include "constants.h"  // for CONSTANTS *
#include <vector>       // for VECTOR
#include <list>         // for LIST
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
   ptUpperRight(ptUpperRight)
   {
      // initialize the stars
      for (int i = 0; i < NUM_STARS; i++)
      {
         stars[i] = Star(ptUpperRight);
      }
      
//      Satellite * gpsExample = new GPS(Position(21082000.0, 36515095), Velocity(-2685.0, 1550.0));
//      satellites.push_back(gpsExample);
      
      Satellite * gpsExample = new GPS(Position(-6378000.0, 0.0), Velocity(0.0, 0.0));
      satellites.push_back(gpsExample);
      
      
//      // initialize all the satellites
//      Satellite * ship = new Ship;
//      Satellite * sputnik = new Sputnik;
//      Satellite * gps1 = new GPS (Position(0.0, 26560000.0), Velocity(-3880.0, 0.0));
//      Satellite * gps2 = new GPS (Position(23001634.72, 13280000.0), Velocity(-1940.00, 3360.18));
//      Satellite * gps3 = new GPS (Position(23001634.72, -13280000.0), Velocity(1940.00, 3360.18));
//      Satellite * gps4 = new GPS (Position(0.0, -26560000.0), Velocity(0.0, -26560000.0));
//      Satellite * gps5 = new GPS (Position(23001634.72, -13280000.0), Velocity(1940.00, -3360.18));
//      Satellite * gps6 = new GPS (Position(-23001634.72, 13280000.0), Velocity( -1940.00, -3360.18));
//      Satellite * hubble = new Hubble;
//      Satellite * dragon = new Dragon;
//      Satellite * starlink = new Starlink;
//
//      satellites.push_back(ship);
//      satellites.push_back(sputnik);
//      satellites.push_back(hubble);
//      satellites.push_back(dragon);
//      satellites.push_back(starlink);
//      satellites.push_back(gps1);
//      satellites.push_back(gps2);
//      satellites.push_back(gps3);
//      satellites.push_back(gps4);
//      satellites.push_back(gps5);
//      satellites.push_back(gps6);
   }
   
   void update()
   {
      // update the earth
      earth.update();
      
      // update all satellites
      for (int i = 0; i < satellites.size(); i++)
      {
         satellites[i]->update(TIME_PER_FRAME);
         cout << "Position" << satellites[i]->getPosition() << endl;
      }
      
      // handle collisions
      // first create new satellites
      // then destroy collided satellites
   }
   
   void draw()
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

private:
   Earth earth;
   vector<Satellite *> satellites;
   Position ptUpperRight;
   Star stars[NUM_STARS];     // the star array
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Demo* pDemo = (Demo*)p;
   
   pDemo->draw();
   pDemo->update();

}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Test
//   testRunner();
   
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Orbital",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}

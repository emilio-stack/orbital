/*************************************************************
 * 1. Name:
 *      Emilio Regino & Bradley Payne
 * 2. Assignment Name:
 *      Lab 08: Orbit Simulator Final Submission
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was debugging why the orbits were
 *      not destroying correctly. When a satellite would
 *      destroy the parts created from it would be created
 *      in some really bizzare positions. But after
 *      troubleshooting it was discovered that the magnitude
 *      of the kick applied was not yet sufficient and that
 *      fixed the bug. There was also a bug in offsetting
 *      the GPS RIGHT and LEFT satellites twice when
 *      their draw functions were called.
 * 5. How long did it take for you to complete the assignment?
 *      ~7 hours
 *****************************************************************/

#include "test.h"       // for TEST RUNNER
#include "simulator.h"  // for SIMULATOR
using namespace std;

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
   Simulator* pDemo = (Simulator*)p;
   
   pDemo->input(pUI);
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
   testRunner();
   
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Orbital",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Simulator demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}

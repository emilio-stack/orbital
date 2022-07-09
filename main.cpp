//
//  main.cpp
//  orbitPrototypeMath
//
//  Created by Emilio on 6/1/22.
//
#include <cmath>
#include <iostream>

using namespace std;

/*************************************************************************
 * GET TIME DILATION
 * Compute the time dilation.
 *
 * td = hoursDay x minutesHour
 * Where:
 *    td = time dilation, which is the ratio of simulator time to real-world time
 *    hoursDay = number of hours in a day, 24 in the case of earth
 *    minutesHour = number of minutes in an hour, which is 60 in our case
 *************************************************************************/
double getTimeDilation()
{
   
   return 24.0 * 60.0; /*24 hours in a day X 60 minutes in an hour*/
}

/*************************************************************************
 * GET TIME PER FRAME
 * Compute the time per frame of the simulator.
 *
 * tpf = td / frameRate
 * Where:
 *    tpf = time per frame, which is real-world time in seconds for each frame in the simulator
 *    td = time dilation
 *    frameRate = number of frames in the simulator per second, 30 in our case
 *************************************************************************/
double getTimePerFrame()
{
   double td = getTimeDilation();
   return td / 30.0;
}

/*************************************************************************
 * GET ROTATION SPEED
 * Compute the rotation speed of the earth in the simulator
 *
 * rf = -(2 π / frameRate) x (td / secondsDay)
 * Where:
 *    rf = rotation of the earth in radians for one frame
 *    frameRate = number of frames per second. 30 frames per second in our case
 *    td = how much faster time passes in the simulator than in the real world
 *    secondsDay = number of seconds for the earth to make one rotation
 *************************************************************************/
double getRotationSpeed()
{
   double td = getTimeDilation();

   return -(2.0 * M_PI / 30.0) * (td / 86400.0);
}

/*************************************************************************
 * COMPUTE GRAVITY
 * Compute the magnitude of acceleration due to gravity at a
 * given altitude
 *
 * gh = g ( r / (r + h)) **2
 * Where:
 *    gh = magnitude of acceleration due to gravity at an altitude (h)
 *    g = gravity at sea level: 9.80665 m/s2
 *    r = radius of the earth: 6,378,000 m
 *    h = height above the earth in meters
 *************************************************************************/
double computeGravity(double h)
{
   double g = -9.80665;
   double r = 6378000.0;
   double base = (r / (r + h));
   return  g * (base * base);
}

/*************************************************************************
 * ALTITUDE ABOVE THE EARTH
 * Compute the height above the earth given the position of an object
 *
 * h = √ (x2 + y2) - r
 * Where:
 *    h = height above the earth in meters
 *    x = horizontal position of the satellite where the center of the earth is 0
 *    y = vertical position of the satellite where the center of the earth is 0
 *    r = radius of the earth: 6,378,000 m
 *************************************************************************/
double computeAltitude(double x, double y)
{
   return sqrt((x * x) + (y * y)) - 6378000.0;
}

/*************************************************************************
 * Direction of gravity pull
 * compute the direction of the pull of gravity
 *
 * d = atan(xe - xs, ye - ys)
 * Where:
 *    d = direction of the pull of gravity, in radians
 *    xe = horizontal position of the center of the earth: 0 m
 *    ye = vertical position of the center of the earth: 0 m
 *    xs = horizontal position of the satellite in meters
 *    ys = vertical position of the satellite in meters
 *************************************************************************/
double computeGravPullDirection(double xS, double yS)
{
   // -  (-xS) direction is positive
   return atan2(-(-xS), -(-yS));  /* -xS is same thing as 0.0 - xS */
}

/*******************************************************************
 *  CALCULATE HORIZONTAL COMPONENT
 *  A function to calculate the horizontal component of acceleration
 *
 *  dx = s sin(a)
 *  Where:
 *    s = overall speed (m/s)
 *    a = directon of travel where 0 is pointing up (radians)
 * *******************************************************************/

double calcHorComp(double speed, double angle)
{
   return speed * sin(angle);
}

/*******************************************************************
 *  CALCULATE VERTICAL COMPONENT
 *  A function to calculate the vertical component of acceleration
 *
 *  dy = s cos(a)
 *  Where:
 *    dy = vertical component of speed (m/s)
 *    s = overall speed (m/s)
 *    a = directon of travel where 0 is pointing up (radians)
 * *******************************************************************/
double calcVertComp(double speed, double angle)
{
   return speed * cos(angle);
}

/*******************************************************************
 *  CALC DISTANCE
 *  A function to calculate distance
 *
 *  s = s0 + v t + ½ a t ** 2
 *  Where:
 *    s = distance in meters (m)
 *    s0 = initial distance (m)
 *    v = velocity (m/s)
 *    t = time (s)
 *    a = acceleration (m/s2)
 * *******************************************************************/
double calcDistance(double distanceInit, double velocity, double acceleration)
{
   double time = getTimePerFrame();
   
   return distanceInit + (velocity * time) + (0.5 * acceleration * (time * time));
}

/*******************************************************************
 *  CALC VELOCITY
 *  A function to calculate velocity with constant acceleration
 *
 *  v = v0 + a t
 *  Where:
 *    v = velocity in meters (m/s)
 *    v0 = initial velocity (m/s)
 *    a = acceleration (m/s2)
 *    t = time (s)
 * *******************************************************************/
double calcVelocity(double velocityInit, double acceleration)
{
   double time = getTimePerFrame();
   
   return velocityInit + (acceleration * time);
}

void play(double & i, double & j)
{
   double x = i;
   double y = j;
   double altitude = computeAltitude(x, y);
   double gravity = computeGravity(altitude);
   double direction = computeGravPullDirection(x, y);
   double horizontal = calcHorComp(gravity, direction);
   double vertical = calcVertComp(gravity, direction);
   double velocityX = calcVelocity(-2685.0 /* Cathetus */,  horizontal);
   double velocityY = calcVelocity(1550.0 /* Cathetus */,  vertical);
   double newX = calcDistance(x, velocityX, horizontal);
   double newY = calcDistance(y, velocityY, vertical);
   
//   cout << "Time Dilation:  " << getTimeDilation()    << endl;
//   cout << "Time Per Frame: " << getTimePerFrame()    << endl;
//   cout << "Rotation Speed: " << getRotationSpeed()   << endl;
//   cout << "Altitude:       " << altitude             << endl;
//   cout << "Grav:           " << gravity              << endl;
//   cout << "AccelY:       " << vertical             << endl;
//   cout << "Velocity X:     " << velocityX            << endl;
//   cout << "Velocity Y:     " << velocityY            << endl;
//   cout << "New Y Position: " << newY                 << endl;

   cout << "Position:      " << newX << ", " << newY << endl;
   cout << "Altitude:      " << altitude             << endl;
   cout << "Magnitude:     " << gravity              << endl;
   cout << "Angle:         " << direction            << endl;
   cout << "Gravity:       " << horizontal << ", " << vertical << endl;
   cout << "Velocity:      " << velocityX << ", " << velocityY << endl;
   cout << endl;
   
   
   i = newX;
   j = newY;
}

/*************************************************************************
 * Main
 * Figure out the math for the orbital simulator
 *************************************************************************/
int main(int argc, const char * argv[]) {
   
   double x = 21082000.0;
   double y = 36515095.0;
   while (true)
      play(x, y);
   
   return 0;
}

/***********************************************************************
 * Header File:
 *    Constants : All of the constants in the orbital simulator
 * Author:
 *    Emilio Regino, Bradley Payne, Penelope Sanchez
 * Summary:
 *    This contains all of the global constants for the orbital simulator
 ************************************************************************/

#pragma once

const int NUM_STARS = 200;
const double TIME_DILATION = 24.0 * 60.0; /* 24 hours in a day X 60 minutes in an hour */
const double FRAME_RATE = 30.0;
const double TIME_PER_FRAME = TIME_DILATION / FRAME_RATE;
const double EARTH_RADIUS = 6378000.0;
const double ANGULAR_VELOCITY = 0.2;
const double GRAVITY = -9.80665;

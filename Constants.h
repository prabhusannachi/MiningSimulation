/**
 * @file  Constants.h
 *
 * This file contains constants specific to calculate
 * truck's travel time, loading and unloading time.
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <iostream>
// Number of seconds per minute
static const uint32_t kSecondsPerMinute = 60;
// Number of minutes per hour
static const uint32_t kMinutePerHour = 60;
// Number of milliseconds per second
static const uint32_t kMilliSecondsPerSecond = (uint32_t)1000;
/*
*  Mining Truck Travel time between mining site and unloading
*  station in Minute
*/
static const uint32_t kTravelTimeInMinute = 30;
//Time taken to unloading mine in minute
static const uint32_t kUnloadingTimeInMinute = 5;
//Minimum loading time taken to load the mine in hour
static const uint32_t kMinloadingTimeInHour = 1;
//Maximum loading time taken to load the mine in hour
static const uint32_t kMaxloadingTimeInHour = 5;
//Total simulation time in hour to run the test
static const uint32_t kSimulationTimeInHour = 72;
//Factor value to reduce the time to speed up the test
static const uint32_t kFactorValue = 100;

#endif /* CONSTANTS_H_ */

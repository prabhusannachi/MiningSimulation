/**
 * @file  UnloadingStation.cpp
 *
 * This file contains UnloadingStation class methods implementation.
 */

#include <chrono>
#include <thread>
#include "UnloadingStation.h"


UnloadingStation::UnloadingStation(uint16_t stationId)
{
	m_stationId = stationId;
	m_unloadCount = 0;
	m_stopSim = false;
	m_unloadingTruck = NULL;
	m_startTime = high_resolution_clock::now();
}

void UnloadingStation::IncrementUnloadCount()
{
	m_unloadCount++;
}

void UnloadingStation::StopSimulation()
{
	m_stopSim = true;
}

void UnloadingStation::PushToQueue(MiningTruck* truck)
{
	m_queue.push(truck);
}

uint64_t UnloadingStation::GetWaitingTime()
{
	uint64_t totalTime = 0;
	// Calculate total waiting time by multiplying queue size and unloading time in seconds (5*60).
	// then add the remaining time of currently unloading truck (5*60 - elapsed time)
	// Elapsed time is calculated by std::chrono::duration_cast< std::chrono::seconds>(high_resolution_clock::now() - m_startTime)
	return totalTime;
}

void UnloadingStation::run()
{
	while(!m_stopSim)
	{
		if(m_queue.pop(m_unloadingTruck, 1000))
		{
			m_startTime = high_resolution_clock::now();
			this_thread::sleep_for(std::chrono::milliseconds(MiningTruck::GetUnloadingTime()));
			m_unloadingTruck->NotifyUnloadingCompletion();
		}
	}
}

ostream & operator << (ostream &out, const UnloadingStation &station)
{
    out << station.m_stationId;
    //construct all the inputs needed to print.
    return out;
}



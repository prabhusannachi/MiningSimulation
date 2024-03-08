/**
 * @file  UnloadingStation.h
 *
 * This file contains UnloadingStation class.
 */

#ifndef UNLOADINGSTATION_H_
#define UNLOADINGSTATION_H_

#include <iostream>
#include <unistd.h>
#include <chrono>
#include "BlockingQueue.h"
#include "MiningTruck.h"

using namespace std::chrono;

class UnloadingStation
{
public:
	/**
	 * Constructor
	 * @param[in] stationId Identifier of the station
	 */
	UnloadingStation(uint16_t stationId);
	/**
	* Increment the unloading count of the station
	* It is used to generate statistics report.
	*/
	void IncrementUnloadCount();
    /**
     * Method to stop the simulation.
     */
	void StopSimulation();
	/**
	 * Get current wait time in the queue to unload the mine
	 *
	 * @return Time in milliseconds
	 */
	uint64_t GetWaitingTime();
	/**
	 * Add the truck in the waiting queue of the station to unload the mine
	 * @param[in] truck   Truck to unload
	 */
	void PushToQueue(MiningTruck* truck);
	/**
	 * Runnable method to start by thread to initiate station's work
	 */
	void run();
	/**
	 * Ostream operator overloading for UnloadingStation class
	 *
	 * @param[in] out Ostream
	 * @param[in] truck UnloadingStation object
	 */
	friend ostream & operator << (ostream &out, const UnloadingStation &station);

private:
	// Station Identifier
	uint16_t m_stationId;
	// Stores the number of times unloading happens in the station
	uint8_t m_unloadCount;
	// Queue to put the truck to unload
	BlockingQueue<MiningTruck*> m_queue;
	//Stops the simulation
	volatile bool m_stopSim;
	//Current unloading truck object.
	MiningTruck* m_unloadingTruck;
	//Stores the time when truck starts to unload activity
	high_resolution_clock::time_point m_startTime;
};

#endif /* UNLOADINGSTATION_H_ */

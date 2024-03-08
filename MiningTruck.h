/**
 * @file  MiningTruck.h
 *
 * This file contains TruckState enumeration values
 * and MiningTruck class.
 *
 */

#ifndef MININGTRUCK_H_
#define MININGTRUCK_H_

#include <iostream>
#include <unistd.h>
#include <mutex>
#include <condition_variable>

using namespace std;

/**
 * TruckState Enumeration.
 * It is used to represent the state of MiningTruck object.
 */
typedef enum TruckState {
    empty = 0,
    travel_to_mine_site = 1,
	travel_to_unloading_station = 2,
	approaching_to_mine_site = 3,
	loading_mine = 4,
	approaching_unloading_station = 5,
	unloading = 6,
	waiting_in_queue = 7
} TruckState;

/**
 * MiningTruck Class
 */
class MiningTruck
{
public:
   /**
	* Constructor
	*
	* @param[in] truckId Identifier of the truck
	*/
	MiningTruck(uint16_t truckId);
   /**
	* Get the current state of the truck
	*
	* @return   TruckState  Returns the current state of the truck
	*                       TruckState enumeration data type is used to
	*                       represent the current state of the truck
	*/
	TruckState GetTruckState();
   /**
	* Set the current state of the truck
	*
	* @param[in] newState New state value of the truck
	*            TruckState enumeration data type is used to
	*            represent the new state of the truck
	*/
	void SetTruckState(TruckState newState);
   /**
	* Increment the travel count of the mining truck
	* from mining site to unloading station and vice versa.
	* It is used to generate statistics report.
	*/
	void IncrementTravelCount();
   /**
	* Increment the unloading count of the mining truck
	* It is used to generate statistics report.
	*/
	void IncrementUnloadCount();
   /**
	* Update the loading time of the mining truck.
	* It is used to generate statistics report.
	*
	* @param[in] loadingTime Loading time in milliseconds
	*/
	void UpdateLoadingTime(uint64_t loadingTime);
   /**
	* Wait for unloading to be completed.
	* It uses conditional variable wait function.
	*/
	void WaitForUnloadingCompletion();
   /**
	* Notify the unloading process completion
	* It uses conditional variable notify function.
	* It is called from Unloading object once it is
	* done unloading completion work.
	*/
	void NotifyUnloadingCompletion();
	/**
	 * Stop the simulation
	 */
	void StopSimulation();
	/**
	 * Wait method. Truck waits for the given period.
	 *
	 * @param[in] waitTime Wait time in milliseconds
	 *
	 * @return    bool  True if it waits for the given time,
	 *                  otherwise False if it is interrupted
	 */
	bool Wait(int waitTime);
	/**
	 * Get Travel time of truck between mining site and
	 * unloading station
	 *
	 * @return   Integer Time in milliseconds
	 */
	static int GetTravelTime();
	/**
	 * Get Loading time to load the mine
	 *
	 * @return   Integer Time in milliseconds
	 */
	static int GetLoadingTime();
	/**
	 * Get Unloading time to unload the mine at the station
	 *
	 * @return   Integer Time in milliseconds
	 */
	static int GetUnloadingTime();
	/**
	 * Ostream operator overloading for Mining Truck class
	 *
	 * @param[in] out Ostream
	 * @param[in] truck Mining Truck object
	 *
	 * @return    ostream  ostream object
	 */
	friend ostream & operator << (ostream &out, const MiningTruck &truck);

private:
	// Truck Id
	uint16_t m_truckId;
	//Number of times truck travels between site and unloading station
	uint8_t m_travelCount;
	//Number of times truck unloads the mine.
	uint8_t m_unloadCount;
	//Number of times truck is loaded
	uint8_t m_loadCount;
	//Total loading times used by truck to load the mine
	uint32_t m_totalLoadingTime;
	//Truck current state
	TruckState m_truckState;
	//Mutex object used by conditional variable m_signal
	mutable std::mutex m_guard;
	//Conditional variable used for unloading completion status
	std::condition_variable m_signal;
	//Conditional variable used for waiting time
	std::condition_variable m_waitSignal;
	//Mutex object used by conditional variable m_waitSignal
	mutable std::mutex m_waitMutex;
};

#endif /* MININGTRUCK_H_ */

/**
 * @file  StateExecutor.h
 *
 * This file contains StateExecutor class.
 */
#ifndef STATEEXECUTOR_H_
#define STATEEXECUTOR_H_

#include "MiningTruck.h"
#include "UnloadingStation.h"
#include "State.h"

class StateExecutor
{
public:
    /**
	* Executes the work for the given truck.
	*
	* @param[in] truck               MiningTruck object which should be handled.
	* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
	*                                the shortest waiting time and push the truck into
	*                                queue of that station.
	*/
    void execute(MiningTruck* const truck, std::vector<UnloadingStation*> unloadingStations);
    /**
     * Method to stop the simulation.
     */
    void StopSimulation();
private:
	/**
	 * Get the instance of State's derived class based truck's current state
	 *
	 * @param[in] truckState Truck's current state
	 *
	 * @return    Instance of State object based on the current state
	 */
    State* GetStateInstance(TruckState truckState);
    // Variable to stop the thread
    volatile bool m_stopSim;
};
#endif /* STATEEXECUTOR_H_ */

/**
 * @file  State.h
 *
 * This file contains State abstract class and
 * all required derived class to match with TruckState
 * enumeration values.
 */

#ifndef STATE_H_
#define STATE_H_

#include "MiningTruck.h"
#include "UnloadingStation.h"

/**
 * State abstract class
 * Used to be derived by other state class.
 */
class State
{
    public:
	    /**
		* Handles the truck based on the its current state.
		* It does the corresponding state's task, then move
		* to next state
		*
		* @param[in] truck               MiningTruck object which should be handled.
		* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
		*                                the shortest waiting time and push the truck into
		*                                queue of that station.
		*/
    	void Handle(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations);
    	/**
    	 * Destructor
    	 */
    	virtual ~State();
    private:
	    /**
		* Do the work for the state of the truck
		*
		* @param[in] truck               MiningTruck object which should be handled.
		* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
		*                                the shortest waiting time and push the truck into
		*                                queue of that station.
		*/
    	virtual void DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations);
	    /**
		* Return the next state after current state. It is abstract method.
		* It should be overridden by all derived class.
		*
		* @return    TruckState  Returns the next state value after the current state.
		*                        Next state is TruckState data type.
		*/
    	virtual TruckState NextTruckState() = 0;
};

/**
 * Empty State class
 */
class Empty: public State
{
public:
    /**
	* Method to get the singleton instance of Empty class.
	*
	* @return  Returns the singleton instance of Empty class.
	*/
    static Empty* GetInstance();
	/**
	 * Destructor
	 */
    ~Empty();
private:
    /**
	* Return the next state after empty state.
	*
	* @return    TruckState  Returns the next state value after the empty state.
	*                        Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

/**
 * TravelToMineSite State class
 */
class TravelToMineSite: public State
{
public:
    /**
	* Method to get the singleton instance of UnloadingStation class.
	*
	* @return  Returns the singleton instance of UnloadingStation class.
	*/
    static TravelToMineSite* GetInstance();
	/**
	 * Destructor
	 */
    ~TravelToMineSite();
private:
    /**
	* Do the work for TravelToMineSite state
	*
	* @param[in] truck               MiningTruck object which should be handled.
	* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
	*                                the shortest waiting time and push the truck into
	*                                queue of that station.
	*/
    void DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations);
    /**
	* Return the next state after travel_to_mine_site state.
	*
	* @return    TruckState  Returns the next state value after the travel_to_mine_site state.
	*                        Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

/**
 * TravelToUnloadingStation State class
 */
class TravelToUnloadingStation: public State
{
public:
    /**
	* Method to get the singleton instance of UnloadingStation class.
	*
	* @return  Returns the singleton instance of UnloadingStation class.
	*/
    static TravelToUnloadingStation* GetInstance();
	/**
	 * Destructor
	 */
    ~TravelToUnloadingStation();
private:
    /**
	* Do the work for TravelToMineSite state
	*
	* @param[in] truck               MiningTruck object which should be handled.
	* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
	*                                the shortest waiting time and push the truck into
	*                                queue of that station.
	*/
    void DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations);
    /**
	* Return the next state after travel_to_unloading_station state.
	*
	* @return    TruckState   Returns the next state value after the travel_to_unloading_station state.
	*                         Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

/**
 * ApproachingToMineSite State class
 */
class ApproachingToMineSite: public State
{
public:
    /**
	* Method to get the singleton instance of ApproachingToMineSite class.
	*
	* @return  Returns the singleton instance of ApproachingToMineSite class.
	*/
    static ApproachingToMineSite* GetInstance();
	/**
	 * Destructor
	 */
    ~ApproachingToMineSite();
private:
    /**
	* Return the next state after approaching_to_mine_site state.
	*
	* @return    TruckState    Returns the next state value after the approaching_to_mine_site state.
	*                          Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

/**
 * ApproachingToUnloadingStation State class
 */
class ApproachingToUnloadingStation: public State
{
public:
    /**
	* Method to get the singleton instance of ApproachingToUnloadingStation class.
	*
	* @return  Returns the singleton instance of ApproachingToUnloadingStation class.
	*/
    static ApproachingToUnloadingStation* GetInstance();
	/**
	 * Destructor
	 */
    ~ApproachingToUnloadingStation();
private:
    /**
	* Return the next state after approaching_unloading_station state.
	*
	* @return   TruckState   Returns the next state value after the approaching_unloading_station state.
	*                        Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

/**
 * LoadingMine State class
 */
class LoadingMine: public State
{
public:
    /**
	* Method to get the singleton instance of LoadingMine class.
	*
	* @return  Returns the singleton instance of LoadingMine class.
	*/
    static LoadingMine* GetInstance();
	/**
	 * Destructor
	 */
    ~LoadingMine();
private:
    /**
	* Do the work for LoadingMine state
	*
	* @param[in] truck               MiningTruck object which should be handled.
	* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
	*                                the shortest waiting time and push the truck into
	*                                queue of that station.
	*/
    void DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations);
    /**
	* Return the next state after loading_mine state.
	*
	* @return    TruckState   Returns the next state value after the loading_mine state.
	*                         Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

/**
 * Unloading State class
 */
class Unloading: public State
{
public:
    /**
	* Method to get the singleton instance of Unloading class.
	*
	* @return  Returns the singleton instance of Unloading class.
	*/
    static Unloading* GetInstance();
	/**
	 * Destructor
	 */
    ~Unloading();
private:
    /**
	* Do the work for Unloading state
	*
	* @param[in] truck               MiningTruck object which should be handled.
	* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
	*                                the shortest waiting time and push the truck into
	*                                queue of that station.
	*/
    void DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations);
    /**
	* Return the next state after unloading state.
	*
	* @return    TruckState   Returns the next state value after the unloading state.
	*                         Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

/**
 * WaitingInQueue State class
 */
class WaitingInQueue: public State
{
public:
    /**
	* Method to get the singleton instance of WaitingInQueue class.
	*
	* @return  Returns the singleton instance of WaitingInQueue class.
	*/
    static WaitingInQueue* GetInstance();
	/**
	 * Destructor
	 */
    ~WaitingInQueue();
private:
    /**
	* Do the work for WaitingInQueue state
	*
	* @param[in] truck               MiningTruck object which should be handled.
	* @param[in] unloadingStations   List of UnloadingStation objects. It is used to get
	*                                the shortest waiting time and push the truck into
	*                                queue of that station.
	*/
    void DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations);
    /**
	* Return the next state after waiting_in_queue state.
	*
	* @return    TruckState   Returns the next state value after the waiting_in_queue state.
	*                         Next state is TruckState data type.
	*/
    TruckState NextTruckState();
};

#endif /* STATE_H_ */

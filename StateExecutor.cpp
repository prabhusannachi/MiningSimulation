/**
 * @file  StateExecutor.cpp
 *
 * This file contains StateExecutor class methods implementation.
 */
#include "StateExecutor.h"

State* StateExecutor::GetStateInstance(TruckState truckState)
{
	State* stateInstance = NULL;
	switch (truckState) {
		case TruckState::empty:
			stateInstance = Empty::GetInstance();
			break;
		case TruckState::travel_to_mine_site:
			stateInstance = TravelToMineSite::GetInstance();
			break;
		// add case for all enumeration values.
		default:
			break;
	}
	return stateInstance;
}

void StateExecutor::StopSimulation()
{
	m_stopSim = true;
}

void StateExecutor::execute(MiningTruck* const truck, std::vector<UnloadingStation*> unloadingStations)
{
	while (!m_stopSim)
	{
		State* const stateInstance = GetStateInstance(truck->GetTruckState());
		if (stateInstance)
		{
			stateInstance->Handle(truck, unloadingStations);
		}
	}
}

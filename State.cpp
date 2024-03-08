/**
 * @file  State.cpp
 *
 * State and all the derived class methods implementation
 */

#include <limits.h>
#include <chrono>
#include <thread>
#include "State.h"


void State::Handle(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations)
{
	DoTask(truck, unloadingStations);
	truck->SetTruckState(NextTruckState());
}

virtual void State::DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations)
{
	//Some state do nothing.
}

static Empty* Empty::GetInstance()
{
	static Empty m_instance;
	return &m_instance;
}
TruckState Empty::NextTruckState()
{
	return TruckState::travel_to_mine_site;
}

static TravelToMineSite* TravelToMineSite::GetInstance()
{
	static TravelToMineSite m_instance;
	return &m_instance;
}

void TravelToMineSite::DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations)
{
	if (truck->Wait(MiningTruck::GetTravelTime()))
	{
		truck->IncrementTravelCount();
	}
}

TruckState TravelToMineSite::NextTruckState()
{
	return TruckState::approaching_to_mine_site;
}

static TravelToUnloadingStation* TravelToUnloadingStation::GetInstance()
{
	static TravelToUnloadingStation m_instance;
	return &m_instance;
}

void TravelToUnloadingStation::DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations)
{
	if (truck->Wait(MiningTruck::GetTravelTime()))
	{
		truck->IncrementTravelCount();
	}
}

TruckState TravelToUnloadingStation::NextTruckState()
{
	return TruckState::approaching_unloading_station;
}

static ApproachingToMineSite* ApproachingToMineSite::GetInstance()
{
	static ApproachingToMineSite m_instance;
	return &m_instance;
}
TruckState ApproachingToMineSite::NextTruckState()
{
	return TruckState::loading_mine;
}

static ApproachingToUnloadingStation* ApproachingToUnloadingStation::GetInstance()
{
	static ApproachingToUnloadingStation m_instance;
	return &m_instance;
}

TruckState ApproachingToUnloadingStation::NextTruckState()
{
	return TruckState::unloading;
}

static LoadingMine* LoadingMine::GetInstance()
{
	static LoadingMine m_instance;
	return &m_instance;
}

void LoadingMine::DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations)
{
	uint64_t loadingTime = MiningTruck::GetLoadingTime();
	if (truck->Wait(loadingTime))
	{
		truck->UpdateLoadingTime(loadingTime);
	}
}

TruckState LoadingMine::NextTruckState()
{
	return TruckState::travel_to_unloading_station;
}

static Unloading* Unloading::GetInstance()
{
	static Unloading m_instance;
	return &m_instance;
}

void Unloading::DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations)
{
	truck->WaitForUnloadingCompletion();
	truck->IncrementUnloadCount();
}

TruckState Unloading::NextTruckState()
{
	return TruckState::empty;
}

static WaitingInQueue* WaitingInQueue::GetInstance()
{
	static WaitingInQueue m_instance;
	return &m_instance;
}

void WaitingInQueue::DoTask(MiningTruck* const truck, std::vector<UnloadingStation*>& unloadingStations)
{
	uint64_t shortWaitTime = INT_MAX;
	UnloadingStation* stationToUnload = NULL;
	for(UnloadingStation* station : unloadingStations)
	{
		uint64_t waitTime = station->GetWaitingTime();
		if (waitTime < shortWaitTime) {
			stationToUnload = station;
			shortWaitTime = waitTime;
		}
	}
	if (stationToUnload) {
		stationToUnload->PushToQueue(truck);
	}
}

TruckState WaitingInQueue::NextTruckState()
{
	return TruckState::empty;
}

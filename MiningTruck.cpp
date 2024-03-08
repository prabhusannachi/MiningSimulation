/**
 * @file  MiningTruck.cpp
 *
 * MiningTruck class methods implementation
 */

#include "MiningTruck.h"
#include "Constants.h"

MiningTruck::MiningTruck(uint16_t truckId)
{
	m_truckId = truckId;
	m_travelCount = 0;
	m_unloadCount = 0;
	m_loadCount = 0;
	m_totalLoadingTime = 0;
	m_truckState = TruckState::empty;
}
TruckState MiningTruck::GetTruckState()
{
	return m_truckState;
}
void MiningTruck::SetTruckState(TruckState newState)
{
	m_truckState = newState;
}
void MiningTruck::IncrementTravelCount()
{
	m_travelCount++;
}
void MiningTruck::IncrementUnloadCount()
{
	m_unloadCount++;
}

void MiningTruck::UpdateLoadingTime(uint64_t loadingTime)
{
	m_totalLoadingTime += loadingTime;
	m_loadCount++;
}

void MiningTruck::WaitForUnloadingCompletion()
{
	  std::unique_lock<std::mutex> lock(m_guard);
	  m_signal.wait(lock);
}

void MiningTruck::NotifyUnloadingCompletion()
{
	  std::unique_lock<std::mutex> lock(m_guard);
	  m_signal.notify_one();
}

static int MiningTruck::GetTravelTime()
{
	return (kTravelTimeInMinute * kSecondsPerMinute * kMilliSecondsPerSecond) / kFactorValue;
}

static int MiningTruck::GetLoadingTime()
{
	int loadingTime;
	//Get random value between minimum loading time in milliseconds and maximum loading time in milliseconds.
	//Then divide by factor value
	return loadingTime;
}

static int MiningTruck::GetUnloadingTime()
{
	int unloadingTime;
	//Get random value between minimum loading time in milliseconds and maximum loading time in milliseconds.
	//Then divide by factor value
	return unloadingTime;
}

ostream & operator << (ostream &out, const MiningTruck &truck)
{
    out << truck.m_truckId;
    //construct all the inputs needed to print.
    return out;
}

void MiningTruck::StopSimulation()
{
	  std::unique_lock<std::mutex> lock(m_waitMutex);
	  m_waitSignal.notify_one();
}

bool MiningTruck::Wait(int waitTime)
{
	  //use condition variable wait_for function to wait until given wait time.
	  // It return true if it is timeout. False if it is not timed out and awaken by
	 // stop simulation function.
	return true;
}




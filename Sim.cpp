/**
 * @file  Sim.cpp
 *
 * This file contains Main function to start and methods to print the
 * trucks and stations statistics report.
 */
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include "MiningTruck.h"
#include "UnloadingStation.h"
#include "StateExecutor.h"
#include "Constants.h"
using namespace std;
using namespace std::chrono;

/**
 * Print all trucks statistics report
 *
 * @param[in] trucks        List of MiningTruck object.
 */
void PrintMiningTruckStatisticsReport(std::vector<MiningTruck*>& trucks)
{
	// loop through each item in trucks and use cout to print all reports.
}

/**
 * Print all unloading station statistics report
 *
 * @param[in] trucks        List of UnloadingStation object.
 */
void PrintUnloadingStationStatisticsReport(std::vector<UnloadingStation*>& stations)
{
	// loop through each item in stations and use cout to print all reports.
}

/**
 * Get the number of trucks to be participated in the simulation test
 * from the user.
 *
 * @return    Integer Number of trucks
 */
int GetTrucksCountFromUser()
{
	int count;
	cout << "Enter number of Trucks : ";
	cin >> count;
	return count;
}

/**
 * Get the number of unloading stations to be participated in the simulation test
 * from the user.
 *
 * @return    Integer Number of unloading stations
 */

int GetUnloadingStationCountFromUser()
{
	int count;
	cout << "Enter number of UnloadingStations : ";
	cin >> count;
	return count;
}

/**
 * Wait until the simulation test completes
 */
void WaitForSimulationEnds()
{
	int simulationTime = (kSimulationTimeInHour * kMinutePerHour * kSecondsPerMinute * kMilliSecondsPerSecond) / kFactorValue;
	this_thread::sleep_for(std::chrono::milliseconds(simulationTime));
}

/**
 * Main Function
 *
 * @return Integer success.
 */
int main() {
	int trucksCount = 0;
	int unloadingStationCount = 0;
	std::vector<MiningTruck*> trucks;
	std::vector<StateExecutor*> executors;
	std::vector<UnloadingStation*> stations;
	std::vector<std::thread> executorThreads;
	std::vector<std::thread> stationThreads;

	//Get Truck counts from user. If user enters value equal or lesser than 0, it will prompt again to get valid value.
	while(1)
	{
		trucksCount = GetTrucksCountFromUser();
		if (trucksCount <= 0) {
			cout <<"Invalid number of Trucks. Please enter valid number. 1 or more";
		} else {
			break;
		}
	}

	//Get Unloading Station counts from user. If user enters value equal or lesser than 0, it will prompt again to get valid value.
	while(1)
	{
		unloadingStationCount = GetUnloadingStationCountFromUser();
		if (trucksCount <= 0) {
			cout <<"Invalid number of Unloading Stations. Please enter valid number. 1 or more";
		} else {
			break;
		}
	}

    /**
	 * Create instance of UnloadingStation for each station
	 * Thread is created for each station which executes unloading process of the truck
	 * from the waiting queue.
	 */
	for(int i=1; i<=unloadingStationCount; ++i) {
		UnloadingStation* station = new UnloadingStation(i);
	    stations.push_back(station);
	    std::thread t = std::thread(&UnloadingStation::run, station);
	    stationThreads.push_back(t);
	}

	/**
	 * Create instance of MiningTruck and StateExecutor for each truck.
	 * Thread is created for each StateExecutor which executes the task of the state for each truck
	 */
	for(int i=1; i<=trucksCount; ++i) {
		MiningTruck* truck = new MiningTruck(i);
		StateExecutor* executor = new StateExecutor();
		trucks.push_back(truck);
		executors.push_back(executor);
	    std::thread t = std::thread(&StateExecutor::execute, executor, truck, stations);
	    executorThreads.push_back(t);
	}

	//Wait until simulation test time completes
	WaitForSimulationEnds();

	//Stop all threads
	for(UnloadingStation* station : stations)
	{
		station->StopSimulation();
	}
	for(StateExecutor* executor : executors)
	{
		executor->StopSimulation();
	}
	for(MiningTruck* truck : trucks)
	{
		truck->StopSimulation();
	}

	//Wait until all threads are terminated
	for(std::thread t : stationThreads)
	{
		try
		{
			t.join();
		} catch(const std::system_error& e) {
	        std::cout << "Caught system_error with code "
	                     "[" << e.code() << "] meaning "
	                     "[" << e.what() << "]\n";
		}
	}
	for(std::thread t : executorThreads)
	{
		try
		{
			t.join();
		} catch(const std::system_error& e) {
	        std::cout << "Caught system_error with code "
	                     "[" << e.code() << "] meaning "
	                     "[" << e.what() << "]\n";
		}
	}

	//Print statistics report
	PrintMiningTruckStatisticsReport(trucks);
	PrintUnloadingStationStatisticsReport(stations);

	//Delete all allocated objects from heap.
	for(UnloadingStation* station : stations)
	{
		delete station;
	}
	for(StateExecutor* executor : executors)
	{
		delete executor;
	}
	for(MiningTruck* truck : trucks)
	{
		delete truck;
	}

	return 0;
}

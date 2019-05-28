#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"
#include "AirShuttle/ServicesPlanner.h"
#include "AirShuttle/AirShuttle.h"
#include "Utils/MapTag.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include<iostream>

using namespace std;

int main() {
	vector<string> maps = {"Aveiro","Braga","Coimbra","Ermesinde","Fafe","Gondomar","Lisboa","Maia","Porto","Viseu"};
	vector<int> aeroports = {1074045106,914277436,248187791,25452377,26130602,112624378,582518618,26058112,PORTO_AIRPORT,26023654};
	
	
	for(unsigned i = 2; i < maps.size();i++){
	Graph graph;
	GraphLoader::loadGraph(maps.at(i), &graph);

	ServicesPlanner planner(&graph, aeroports.at(i), 5);
	//ServicesPlanner planner(&graph, PORTO_AIRPORT, 5);
	planner.addReservationsFromFile(maps.at(i), "reservations_100.txt");
	cout << maps.at(i) <<": ";
	planner.preProcessEntryData();
	graph.dijkstraShortestPath(aeroports.at(i));
	auto start_time = chrono::high_resolution_clock::now();
	//planner.planSingleVanNotMixingPassengers();
	planner.planSingleVanMixingPassengers();
	//planner.planVansFleetMixingPassengers();
	auto finish = chrono::high_resolution_clock::now();
	auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start_time).count();
	cout << mili << "\n";
	break;
	}

	//MapDrawer mapDrawer(2000, 2000);
	//mapDrawer.drawMapFromPlannerSingleVan(&planner);
	cout << "\n";
	//getchar();


//auto start_time = chrono::high_resolution_clock::now();
//auto finish = chrono::high_resolution_clock::now();
//auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start_time).count();



	return 0;
}

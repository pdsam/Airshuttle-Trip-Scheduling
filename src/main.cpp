#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"
#include "AirShuttle/ServicesPlanner.h"
#include "AirShuttle/AirShuttle.h"
#include "Utils/MapTag.h"
#define MAP "Portugal"

using namespace std;

int main() {
	vector<string> maps = {"Aveiro","Braga","Coimbra","Ermesinde","Fafe","Gondomar","Lisboa","Maia","Porto","Viseu"};
	vector<int> aeroports = {1074045106,914277436,248187791,25452377,26130602,112624378,582518618,26058112,PORTO_AIRPORT,26023654};
	for(unsigned i = 0; i < maps.size();i++){
	Graph graph;
	GraphLoader::loadGraph(maps.at(i), &graph);

	ServicesPlanner planner(&graph, aeroports.at(i), 5);
	//ServicesPlanner planner(&graph, PORTO_AIRPORT, 5);
	//planner.addReservationsFromFile(MAP, "reservations_1329449088.txt");
	cout << maps.at(i) <<": ";
	planner.preProcessEntryData();
	//cout <<"\n";
	}
	//graph.dijkstraShortestPath(158862182);

	//planner.planSingleVanNotMixingPassengers();
	//planner.planSingleVanMixingPassengers();
	//planner.planVansFleetMixingPassengers();

	//MapDrawer mapDrawer(2000, 2000);
	//mapDrawer.drawMapFromPlannerSingleVan(&planner);
	cout << "\n";
	//getchar();

	return 0;
}

#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"
#include "AirShuttle/ServicesPlanner.h"
#include "AirShuttle/AirShuttle.h"
#include "Utils/MapTag.h"

using namespace std;

int main() {

	Graph graph;
	GraphLoader::loadGraph("Porto", &graph);

	ServicesPlanner planner(&graph, PORTO_AIRPORT, 1);
	planner.addReservationsFromFile("Porto", "reservations_1329449088.txt");

	graph.dijkstraShortestPath(PORTO_AIRPORT);

	planner.planSingleVanNotMixingPassengers();

	MapDrawer mapDrawer(2000, 2000);
	mapDrawer.drawMapFromPlannerSingleVan(&planner);

	getchar();

	return 0;
}

#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"
#include "AirShuttle/ServicesPlanner.h"
#include "AirShuttle/AirShuttle.h"

using namespace std;

int main() {

	Graph graph;
	GraphLoader::loadGraph("Porto", &graph);

	ServicesPlanner planner(&graph, PORTO_AIRPORT);
	planner.preProcessEntryData();

	/*
	planner.addReservationsFromFile("Porto", "reservations_1329449088.txt");
	for (auto reservation : planner.getReservations())
		cout << reservation.getClientName() << endl;
	*/

	graph.dijkstraShortestPath(planner.getAirport());
	graph.getPath(planner.getAirport(), graph.getVertexSet().at(1000)->getID());

	MapDrawer mapDrawer(2000, 2000);
	mapDrawer.drawMapFromGraph(&graph);
	getchar();

	return 0;
}

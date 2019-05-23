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

	ServicesPlanner planner(&graph, PORTO_AIRPORT, 1);
	planner.addReservationsFromFile("Porto", "reservations_1329449088.txt");

	planner.planSingleVanNotMixingPassengers();

	for (auto service : planner.getVans().at(0).getServices()) {
		cout << "service from " << service.getStart() << " to " << service.getEnd() << endl;
	}

	/*MapDrawer mapDrawer(2000, 2000);
	mapDrawer.drawMapFromGraph(&graph);*/
	//getchar();

	return 0;
}

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
	GraphLoader::loadGraph("Coimbra", &graph);

	ServicesPlanner planner(&graph, 711049847, 100);
	planner.addReservationsFromFile("pi", "reservations_10000.txt");

	graph.dijkstraShortestPath(248187791);

	//planner.preProcessEntryData();

	//planner.planSingleVanNotMixingPassengers();
	//planner.planSingleVanMixingPassengers();
	planner.planVansFleetMixingPassengers();

	int counter = 1;
	for (const Van& v: planner.getVans()) {
		cout << "Van " << counter << ": \n";
		int sCounter = 1;
		for (Service& s: v.getServices()) {
			cout << "\tService " << sCounter << endl;
			cout << "\t\t" << s.getStart() << " -> " << s.getEnd() << "\n";
			cout << "\t\t" << s.getVacant() << "\n\n";

			for (const Reservation& r: s.getReservations()) {
				cout << "\t\t" << r.getClientName() << " - " << r.getArrival() << " -> " << r.getDeliver() << "\n";
			}
			sCounter++;
			cout << endl << endl;
		}
		counter++;
	}

	//graph.DFSConnectivity(graph.findVertex(PORTO_AIRPORT));
	//graph.removeUnvisitedVertices();
	//MapDrawer mapDrawer(2000, 2000);
	//mapDrawer.drawMapFromGraph(&graph);
	//mapDrawer.getViewer()->setVertexColor(474695389 , RED);
	//mapDrawer.getViewer()->setVertexSize(474695389, 5);
	//mapDrawer.getViewer()->setVertexColor(711049847, RED);
	//mapDrawer.getViewer()->rearrange();
	//mapDrawer.drawMapFromPlannerSingleVan(&planner);

	getchar();

	return 0;
}

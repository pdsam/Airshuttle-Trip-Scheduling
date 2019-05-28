#include <iostream>
#include <iomanip>
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

	ServicesPlanner planner(&graph, 711049847, 10);
	planner.addReservationsFromFile("pi", "reservations_1000less.txt");

	graph.dijkstraShortestPath(248187791);

	planner.planVansFleetMixingPassengers();

	MapDrawer mapDrawer(2000, 2000);
	mapDrawer.drawMapFromGraph(&graph);

	multiset<Van> vansSet = planner.getVans();
	vector<Van> vans(vansSet.begin(), vansSet.end());
		
	while (true) {
		cout << "Check services from van [1 - " << vans.size() << "] (-1 to exit) - ";
		int vanIndex;
		cin >> vanIndex;

		if (vanIndex < 0) {
			break;
		}

		Van van = vans.at(vanIndex-1);
		vector<Service> vanServices = van.getServices();
		cout << "See service [1 - " << vanServices.size() << "] (-1 to exit) - ";

		int serviceIndex;
		cin >> serviceIndex;

		if (serviceIndex < 0) {
			break;
		}

		Service service = vanServices.at(serviceIndex-1);

		cout << endl << "Leaves at: " << service.getStart() << endl;
		cout << "Returns at: " << service.getEnd() << endl;
		cout << "Vacant seats: " << service.getVacant() << endl;

		cout << "Serves reservations: " << endl;
		for (const Reservation& r: service.getReservations()) {
			cout << setfill(' ') << setw(10) << r.getClientName() << " - " << setw(10) << r.getNIF() 
			<< setw(8) << ". Arrives at: " << r.getArrival()
			<< setw(8) << ". Delivered at: " << r.getDeliver() << endl;
		}


		for (const Edge& e: service.getPath()) {
			mapDrawer.getViewer()->setEdgeThickness(e.getID(), 10);
			mapDrawer.getViewer()->setEdgeColor(e.getID(), RED);
		}

		mapDrawer.getViewer()->rearrange();

		getchar();
		getchar();

		for (const Edge& e: service.getPath()) {
			mapDrawer.getViewer()->setEdgeThickness(e.getID(), 1);
			mapDrawer.getViewer()->setEdgeColor(e.getID(), BLACK);
		}

		mapDrawer.getViewer()->rearrange();
	}

	getchar();

	return 0;
}

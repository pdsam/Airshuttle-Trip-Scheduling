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

	ServicesPlanner planner(&graph, 711049847, 10);
	planner.addReservationsFromFile("pi", "reservations_1000less.txt");

	graph.dijkstraShortestPath(248187791);

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

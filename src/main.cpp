#include <iostream>
#include <iomanip>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"
#include "AirShuttle/ServicesPlanner.h"
#include "AirShuttle/AirShuttle.h"
#include "Utils/MapTag.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "Usage:" << endl;
		cout << "./airshuttle view <zone>" << endl;
		cout << "./airshuttle preprocess <zone> <node_id>" << endl;
		cout << "./airshuttle astar <zone> <node_id> <node_id2>" << endl;
		cout << "./airshuttle reservations <zone> <reservations_folder> <reservations_file> <airport>" << endl;
		return 0;
	}

	Graph graph;
	MapDrawer mapDrawer(2000, 2000);

	string operation = argv[1];
	if (operation == "view") {
		if (argc < 3) {
			cout << "Not enough argmunents." << endl;
			exit(1);
		}

		GraphLoader::loadGraph(argv[2], &graph);
		mapDrawer.drawMapFromGraph(&graph);

	} else if (operation == "preprocess") {
		if (argc < 4) {
			cout << "Not enough argmunents." << endl;
			exit(1);
		}

		GraphLoader::loadGraph(argv[2], &graph);

		Vertex* source = graph.findVertex(atoi(argv[3]));

		if (source == nullptr) {
			cout << "Vertex not found." << endl;
			exit(1);
		}

		graph.DFSConnectivity(source);
		graph.removeUnvisitedVertices();

		mapDrawer.drawMapFromGraph(&graph);

	} else if (operation == "astar") {
		if (argc < 5) {
			cout << "Not enough arguments." << endl;
			exit(1);
		}

		GraphLoader::loadGraph(argv[2], &graph);

		Vertex* source = graph.findVertex(atoi(argv[3]));
		Vertex* dest = graph.findVertex(atoi(argv[4]));

		if (source == nullptr || dest == nullptr) {
			cout << "Vertex not found." << endl;
			exit(1);
		}

		graph.DFSConnectivity(source);
		graph.removeUnvisitedVertices();

		graph.AStar(atoi(argv[3]), atoi(argv[4]));
		vector<Edge> path = graph.AgetPathEdges(atoi(argv[3]), atoi(argv[4]));

		mapDrawer.drawMapFromGraph(&graph);
		for (const Edge& e: path) {
			mapDrawer.getViewer()->setEdgeThickness(e.getID(), 10);
			mapDrawer.getViewer()->setEdgeColor(e.getID(), RED);
		}

	} else if (operation == "reservations") {
		if (argc < 6) {
			cout << "Not enough arguments." << endl;
			exit(1);
		}

		GraphLoader::loadGraph(argv[2], &graph);

		ServicesPlanner planner(&graph, atoi(argv[5]), 10);
		planner.addReservationsFromFile(argv[3], argv[4]);

		graph.dijkstraShortestPath(atoi(argv[5]));

		planner.planVansFleetMixingPassengers();

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
	}

	getchar();

	return 0;
}

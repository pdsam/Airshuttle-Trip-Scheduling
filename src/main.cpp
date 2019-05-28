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

	ServicesPlanner planner(&graph, aeroports.at(i), 3);
	planner.addReservationsFromFile("Coimbra", "reservations_100.txt");
	planner.preProcessEntryData();
	graph.dijkstraShortestPath(aeroports.at(i));

	planner.planSingleVanNotMixingPassengers();
	//planner.planSingleVanMixingPassengers();
	//planner.planVansFleetMixingPassengers();

/*
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
	*/

	//graph.DFSConnectivity(graph.findVertex(PORTO_AIRPORT));
	//graph.removeUnvisitedVertices();
	//MapDrawer mapDrawer(2000, 2000);
	//mapDrawer.drawMapFromGraph(&graph);
	//mapDrawer.getViewer()->setVertexColor(474695389 , RED);
	//mapDrawer.getViewer()->setVertexSize(474695389, 5);
	//mapDrawer.getViewer()->setVertexColor(PORTO_AIRPORT , RED);
	//mapDrawer.getViewer()->rearrange();
	//mapDrawer.drawMapFromPlannerSingleVan(&planner);
	cout << "\n";
	//getchar();


//auto start_time = chrono::high_resolution_clock::now();
//auto finish = chrono::high_resolution_clock::now();
//auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start_time).count();



	return 0;
}
}

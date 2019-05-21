#include "ServicesPlanner.h"
#include "../Utils/utilities.c"

#include <fstream>
#include <iostream>

using namespace std;

ServicesPlanner::ServicesPlanner(Graph * graph, int airport, int actionRadius, int timeWindow, int maxDist) {
	this->graph = graph;
	this->airport = airport;
	this->actionRadius = max(actionRadius, 1);
	this->timeWindow = max(timeWindow, 1);
	this->maxDist = max(maxDist, 1);
}

int ServicesPlanner::getAirport() const {
	return airport;
}

std::vector<Van> ServicesPlanner::getVans() const {
	return vans;
}

std::multiset<Reservation> ServicesPlanner::getReservations() const {
	return reservations;
}

void ServicesPlanner::addVan(Van van) {
	this->vans.push_back(van);
}

void ServicesPlanner::addReservation(Reservation reservation) {

    Reservation current = move(reservation);

    while (current.getNumPeople() > Van::getCapacity()) {
    	Reservation newRes(current.getClientName(), current.getNIF(), Van::getCapacity(),
    			current.getDest(), current.getArrival());

		current = Reservation(current.getClientName(), current.getNIF(), current.getNumPeople()-Van::getCapacity(),
				current.getDest(), current.getArrival());

    	reservations.insert(newRes);
    }

    reservations.insert(current);

}

bool ServicesPlanner::addReservationsFromFile(string location, string filename) {
	ifstream ifs("reservations/" + location + "/" + filename);
	if(!ifs.is_open()) return false;

	int N;
	ifs >> N;

	string name;
	int nif, node, h, m, s, npersons;
	for (int i = 0 ; i < N; i++) {
		ifs >> name >> nif >> node >> h >> m >> s >> npersons;
		addReservation(Reservation(name, nif, npersons, node, Time(h,m,s)));
	}
	return true;
}

void ServicesPlanner::setActionRadius(int actionRadius) {
	this->actionRadius = max(actionRadius, 1);
}

void ServicesPlanner::setTimeWindow(int timeWindow) {
	this->timeWindow = max(timeWindow, 1);
}

void ServicesPlanner::setMaxDist(int maxDist) {
	this->maxDist = max(maxDist, 1);
}

void ServicesPlanner::preProcessEntryData() {
	/* Pre Process Graph */
	Vertex * start = graph->findVertex(airport);
	if (start == NULL) return;
	graph->DFSConnectivity(start);
	graph->removeUnvisitedVertices();

	/* Pre Process Reservations */
	multiset<Reservation>::iterator it;
	for (it = reservations.begin(); it != reservations.end(); it++) {
		if (graph->findVertex((*it).getDest()) == NULL) {
			it = reservations.erase(it);
			it--;
		}
	}

	/* Reservations were already divided to fit vans size and already sorted due to the use of multiset */
}

void ServicesPlanner::planSingleVanNotMixingPassengers() {
	preProcessEntryData();
	graph->dijkstraShortestPath(airport);

	for (auto reservation : reservations) {
		vector<Edge> pathEdges = graph->getPathEdges(airport, reservation.getDest());
	}
}

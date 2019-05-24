#include "ServicesPlanner.h"
#include <fstream>
#include <iostream>

#include "../Utils/Utilities.h"

using namespace std;

ServicesPlanner::ServicesPlanner(Graph * graph, int airport, int vanCount, int actionRadius, int timeWindow, int maxDist) {
	this->graph = graph;
	this->airport = airport;
	this->vans.resize(vanCount);
	this->actionRadius = max(actionRadius, 1);
	this->timeWindow = max(timeWindow, 1);
	this->maxDist = max(maxDist, 1);
}

Graph * ServicesPlanner::getGraph() const {
	return graph;
}

int ServicesPlanner::getAirport() const {
	return airport;
}

vector<Van> ServicesPlanner::getVans() const {
	return vans;
}

multiset<Reservation> ServicesPlanner::getReservations() const {
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

	Van & van = vans.at(0);
	van.clearServices();

	for (auto reservation : reservations) {
		int services_count = van.getServices().size();

		/* Forward trip */
		vector<Edge> pathEdges = graph->getPathEdges(airport, reservation.getDest());

		Time lastService = services_count > 0 ? van.getServices().at(services_count-1).getEnd() : Time(0,0,0);
		Service newService(&reservation, pathEdges, lastService);

		/* Backward trip */
		reverse(pathEdges.begin(), pathEdges.end());
		for (auto & edge : pathEdges) {
			edge.invertEdge();
		}
		newService.addPath(pathEdges);

		van.addService(newService);
	}
}

vector<Vertex*>::const_iterator getClosestVertexFromList(Vertex* pivot, const vector<Vertex*>& list) {
	
	vector<Vertex*>::const_iterator closest = list.begin();
	double closestDistance = pivot->getPosition().euclidianDistance((*closest)->getPosition());

	for (auto it = list.begin(); it != list.end(); it++) {
		Vertex* v = *it;

		if (v == pivot) {
			continue;
		}

		double tempDist = pivot->getPosition().euclidianDistance(v->getPosition());

		if (tempDist < closestDistance) {
			closest = it;
			closestDistance = tempDist;
		}
	}
	
	return closest;
}

vector<Edge> ServicesPlanner::calculatePath(const std::vector<Vertex*>& reservations) {
	vector<Edge> path;
	vector<Vertex*> tempReservations(reservations.begin(), reservations.end());
	Vertex* airportVertex = graph->findVertex(airport);

	//From airport to first
	//Find closest to airport

	cout << "Getting closest to airport" << endl;	
	auto it = getClosestVertexFromList(airportVertex, tempReservations);
	Vertex* closest = *it;
	cout << "Got it" << endl;

	tempReservations.erase(it);
	
	cout << "Getting path from airport to closest" << endl;
	vector<Edge> fromAirport = graph->getPathEdges(airport, closest->getID());
	path.insert(path.end(), fromAirport.begin(), fromAirport.end());


	//Nearest neighbour approach	
	cout << "Starting nearest neighbour" << endl;
	Vertex* currentSource = closest;
	while(!tempReservations.empty()){
		cout << "Getting closest vertex" << endl;
		auto it = getClosestVertexFromList(currentSource, tempReservations);
		Vertex* closestToSource = *it;
		cout << "Deleting it" << endl;
		tempReservations.erase(it);

		cout << "Getting path " << currentSource->getID() << " " << closestToSource->getID() << endl;
		graph->AStar(currentSource->getID(), closestToSource->getID());
		cout << "Ran algo, getting edges" << endl;
		vector<Edge> tempPath = graph->AgetPathEdges(currentSource->getID(), closestToSource->getID());
		path.insert(path.end(), tempPath.begin(), tempPath.end());

		cout << "Done" << endl << endl;
		currentSource = closestToSource;
	}

	//From final destination back to airport
	graph->AStar(currentSource->getID(), airport);
	vector<Edge> tempPath = graph->AgetPathEdges(currentSource->getID(), airport);
	path.insert(path.end(), tempPath.begin(), tempPath.end());

	return path;
}

void ServicesPlanner::planVansFleetMixingPassengers() {
	while(!reservations.empty()){
		//Get earliest reservation
		Reservation earliest = *reservations.begin();
		reservations.erase(reservations.begin());

		//Find reservation in the next x time
		Time limit = earliest.getArrival() + Time(0,30,0); //In the next 30 minutes

		int accCapacity = earliest.getNumPeople();
		vector<Reservation> service;
		service.push_back(earliest);

		//Search reservations that arrive in the next 30 minutes with 
		//destinations close to the earliest person
		Position origin = graph->findVertex(earliest.getDest())->getPosition();

		multiset<Reservation>::iterator it = reservations.begin();
		while (it->getArrival() < limit && accCapacity <= Van::getCapacity() && it != reservations.end()) {
			Position nodePos = graph->findVertex(it->getDest())->getPosition();
			if (origin.euclidianDistance(nodePos) < 1000) {
				service.push_back(*it);
				accCapacity += it->getNumPeople();
				it = reservations.erase(it);
			} else {
				it++;
			}
		}

		//Calculate path


		//Get path time
		//Update van availability
		//Create the new service
	}
}

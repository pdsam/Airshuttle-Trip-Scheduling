#include "ServicesPlanner.h"
#include <fstream>
#include <iostream>

#include "../Utils/Utilities.h"

using namespace std;

ServicesPlanner::ServicesPlanner(Graph * graph, int airport, int vanCount, int actionRadius, int timeWindow, int maxDist) {
	this->graph = graph;
	this->airport = airport;

	for (int i = 0; i < vanCount; i++) {
		this->vans.insert(Van());
	}

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

multiset<Van> ServicesPlanner::getVans() const {
	return vans;
}

multiset<Reservation> ServicesPlanner::getReservations() const {
	return reservations;
}

void ServicesPlanner::addVan(Van van) {
	this->vans.insert(van);
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

	multiset<Van>::iterator it = vans.begin();
	Van van = *it;
	vans.erase(it);
	van.clearServices();

	for (auto it = reservations.begin(); it != reservations.end();) {
		Reservation reservation = *it;
		it = reservations.erase(it);

		int services_count = van.getServices().size();

		/* Forward trip */
		vector<Edge> pathEdges = graph->getPathEdges(airport, reservation.getDest());

		Time lastService = services_count > 0 ? van.getServices().at(services_count-1).getEnd() : reservation.getArrival();
		vector<Reservation> reservations;
		reservations.push_back(reservation);

		/* Backward trip */
		vector<Edge> returnPath(pathEdges.begin(), pathEdges.end());
		reverse(returnPath.begin(), returnPath.end());
		for (auto & edge : returnPath) {
			edge.invertEdge();
		}
		pathEdges.insert(pathEdges.begin(), returnPath.begin(), returnPath.end());

		Service newService(Van::getCapacity()-reservation.getNumPeople(), lastService, reservations, pathEdges);

		van.addService(newService);
		vans.insert(van);
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

vector<Edge> ServicesPlanner::calculatePath(const std::set<Vertex*>& reservations) {
	vector<Edge> path;
	vector<Vertex*> tempReservations(reservations.begin(), reservations.end());
	Vertex* airportVertex = graph->findVertex(airport);

	//From airport to first
	//Find closest to airport

	auto it = getClosestVertexFromList(airportVertex, tempReservations);
	Vertex* closest = *it;

	tempReservations.erase(it);
	
	vector<Edge> fromAirport = graph->getPathEdges(airport, closest->getID());
	path.insert(path.end(), fromAirport.begin(), fromAirport.end());


	//Nearest neighbour approach	
	Vertex* currentSource = closest;
	while(!tempReservations.empty()){
		auto it = getClosestVertexFromList(currentSource, tempReservations);
		Vertex* closestToSource = *it;
		tempReservations.erase(it);

		graph->AStar(currentSource->getID(), closestToSource->getID());
		vector<Edge> tempPath = graph->AgetPathEdges(currentSource->getID(), closestToSource->getID());
		path.insert(path.end(), tempPath.begin(), tempPath.end());

		currentSource = closestToSource;
	}

	//From final destination back to airport
	graph->AStar(currentSource->getID(), airport);
	vector<Edge> tempPath = graph->AgetPathEdges(currentSource->getID(), airport);
	path.insert(path.end(), tempPath.begin(), tempPath.end());

	return path;
}

Time getTardiestReservationTime(const vector<Reservation>& reservations) {
	Time tardiest = reservations[0].getArrival();
	for (const Reservation& r: reservations) {
		if (tardiest < r.getArrival()) {
			tardiest = r.getArrival();
		}
	}
	return tardiest;
}

void ServicesPlanner::planVansFleetMixingPassengers() {
	while(!reservations.empty()){
		//Get earliest reservation
		Reservation earliest = *reservations.begin();
		reservations.erase(reservations.begin());

		multiset<Van>::iterator earliestVanIt = vans.begin();
		Van van = *earliestVanIt;
		vans.erase(earliestVanIt);
		van.clearServices();

		//Find reservation in the next x time
		//If the earliest available van is not ready in the next 30 minutes,
		//then we can continue looking for passengers until that time
		Time limit = earliest.getArrival() + Time(0,30,0); //In the next 30 minutes
		if (limit < van.getNextTimeAvailable()) {
			limit = van.getNextTimeAvailable();
		}

		int accCapacity = earliest.getNumPeople();
		vector<Reservation> service;
		service.push_back(earliest);

		//Search reservations that arrive in the next 30 minutes with 
		//destinations close to the earliest person
		Position origin = graph->findVertex(earliest.getDest())->getPosition();

		multiset<Reservation>::iterator currentReservationIt = reservations.begin();
		while (currentReservationIt->getArrival() < limit && currentReservationIt != reservations.end()) {

			Position nodePos = graph->findVertex(currentReservationIt->getDest())->getPosition();

			if (origin.euclidianDistance(nodePos) < 1000) {
				if (accCapacity + currentReservationIt->getNumPeople() > Van::getCapacity()) {
					currentReservationIt++;
					continue;
				}
				
				service.push_back(*currentReservationIt);
				accCapacity += currentReservationIt->getNumPeople();

				currentReservationIt = reservations.erase(currentReservationIt);

				if (accCapacity >= Van::getCapacity()) {
					break;
				}
			} else {
				currentReservationIt++;
			}
		}

		//Calculate path
		set<Vertex*> vertexes;
		for_each(service.begin(), service.end(), [&vertexes, this](Reservation res) {
			vertexes.insert(graph->findVertex(res.getDest()));
		});
		vector<Edge> path = calculatePath(vertexes);

		Time timeOfDeparture = getTardiestReservationTime(service);

		//Get path time
		double totalTime = 0;
		for (const Edge& e: path) {
			totalTime += e.getWeight();

			Time timeOfArrivalAtDest = timeOfDeparture;
			timeOfArrivalAtDest.addMinutes(totalTime);

			int vID = e.getDest()->getID();
;
			for (Reservation& r: service) {
				if (r.getAssigned()) {
					continue;
				}

				if (r.getDest() == vID) {
					r.setDeliver(timeOfArrivalAtDest);
				}
			}
		}

		//Update van availability
		Time endOfTripTime = timeOfDeparture;
		endOfTripTime.addMinutes(totalTime);
		van.setNextTimeAvailable(endOfTripTime);

		//Create the new service
		Service vanService(Van::getCapacity()-accCapacity, timeOfDeparture, service, path);
		//Add service to van
		van.addService(vanService);

	}
}
/////////////////////nobody touch my spagetti/////////////////////////////


void ServicesPlanner::planSingleVanMixingPassengers(){
	while(!reservations.empty()){
		Reservation earliest = *reservations.begin();
		reservations.erase(reservations.begin());


	}

	
	multiset<Van>::iterator it = vans.begin();
	Van van = *it;
	vans.erase(it);

	van.clearServices();

	vans.insert(van);
}


/////////////////////////////////////////////////7
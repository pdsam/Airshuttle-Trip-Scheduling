#include "ServicesPlanner.h"
#include <fstream>
#include <iostream>
#include <iostream>
#include <list>

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
	vector<Reservation> toUpdate(reservations.begin(), reservations.end());
	vector<Reservation>::iterator it;
	int counter = 0;
	for (it = toUpdate.begin(); it != toUpdate.end(); it++) {
		if (graph->findVertex((*it).getDest()) == nullptr) {
			cout << "removed: " << counter << "\n";
			it = toUpdate.erase(it);
			counter++;
			it--;
		}
	}

	//cout << "Removed " << counter << " reservations." << endl;

	reservations = multiset<Reservation>(toUpdate.begin(), toUpdate.end());

	/* Reservations were already divided to fit vans size and already sorted due to the use of multiset */
	graph->dijkstraShortestPath(airport);
}

void ServicesPlanner::planSingleVanNotMixingPassengers() {
	//preProcessEntryData();

	multiset<Van>::iterator it = vans.begin();
	Van van = *it;
	vans.erase(it);
	van.clearServices();

	for (auto it = reservations.begin(); it != reservations.end();) {
		Reservation reservation = *it;
		it = reservations.erase(it);
		//cout << "Reservations left:" << reservations.size() << "\n";
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
		pathEdges.insert(pathEdges.end(), returnPath.begin(), returnPath.end());

		Service newService(Van::getCapacity()-reservation.getNumPeople(), lastService, reservations, pathEdges);

		van.addService(newService);
	}
	vans.insert(van);
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
	
	graph->AStar(airport, closest->getID());
	vector<Edge> fromAirport = graph->AgetPathEdges(airport, closest->getID());
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

vector<Reservation> ServicesPlanner::mixClientsWithEarliest(const Reservation & earliest, const Van & van, bool compTimeWindow, bool compMaxDist, int & occupiedSeats) {

	//cout << "Setting time window limit." << endl;
	Time limit = earliest.getArrival() + Time(0,this->timeWindow,0); //In the next 30 minutes
	if (limit < van.getNextTimeAvailable()) {
		limit = van.getNextTimeAvailable();
	}

	vector<Reservation> service;
	service.push_back(earliest);

	Position origin = graph->findVertex(earliest.getDest())->getPosition();

	occupiedSeats = earliest.getNumPeople();

	//cout << "Finding close reservations." << endl;
	//Search reservations that arrive in the next 30 minutes with
	//destinations close to the earliest person
	multiset<Reservation>::iterator currentReservationIt = reservations.begin();
	while (currentReservationIt != reservations.end()) {

		//cout << "Getting nodePos" << endl;
		Position nodePos = graph->findVertex(currentReservationIt->getDest())->getPosition();

		// compare time limit if flag is set
		if (compTimeWindow && limit < currentReservationIt->getArrival()) {
			break;
		}

		// compare distance between nodes only if flag is set
		//cout << "Checking distance" << endl;
		if (!compMaxDist || origin.euclidianDistance(nodePos) < this->maxDist) {
			if (occupiedSeats + currentReservationIt->getNumPeople() > Van::getCapacity()) {
				currentReservationIt++;
				continue;
			}

			service.push_back(*currentReservationIt);
			occupiedSeats += currentReservationIt->getNumPeople();

			currentReservationIt = reservations.erase(currentReservationIt);

			if (occupiedSeats >= Van::getCapacity()) {
				break;
			}
		} else {
			currentReservationIt++;
		}
	}
	return service;
}

void ServicesPlanner::resetVans() {
	int temp = vans.size();
	vans.clear();
	for(int i = 0; i < temp; i++){
		vans.insert(Van());
	}
}

vector<Edge> ServicesPlanner::calculatePathFromService(const vector<Reservation> & service) {
	//cout << "Calculating path." << endl;
	set<Vertex*> vertexes;
	for_each(service.begin(), service.end(), [&vertexes, this](Reservation res) {
		vertexes.insert(graph->findVertex(res.getDest()));
	});
	return calculatePath(vertexes);
}

int ServicesPlanner::assignTimeOfDeliverToReservations(const vector<Edge> & path, vector<Reservation> & service, const Time & timeOfDeparture) {

	for (Reservation& r: service) {
		r.setAssigned(false);
	}

	//cout << "Getting path time" << endl;
	double totalTime = 0;
	for (const Edge& e: path) {
		totalTime += e.getWeight();

		Time timeOfArrivalAtDest = timeOfDeparture.addSeconds(totalTime);

		int vID = e.getDest()->getID();

		for (Reservation& r: service) {
			if (r.getAssigned()) {
				continue;
			}

			if (r.getDest() == vID) {
				r.setDeliver(timeOfArrivalAtDest);
				r.setAssigned(true);
			}
		}
	}
	return totalTime;
}

void ServicesPlanner::planVansFleetMixingPassengers() {
	//cout << "Preprocesing" << endl;
	//preProcessEntryData();

	resetVans();

	//cout << "Starting service creation." << endl << endl;
	while(!reservations.empty()){
		//Get earliest reservation
		//cout << "Getting earliest reservation." << endl;
		Reservation earliest = *reservations.begin();
		reservations.erase(reservations.begin());

		//cout << "Getting earliest available van." << endl;
		multiset<Van>::iterator earliestVanIt = vans.begin();
		Van van = *earliestVanIt;
		vans.erase(earliestVanIt);

		//Mix earliest client with remaining ones
		int occupiedSeats;
		//cout << "Getting sharing clients." << endl;
		vector<Reservation> service = mixClientsWithEarliest(earliest, van, true, false, occupiedSeats);

		//Calculate path
		//cout << "Calculating path." << endl;
		vector<Edge> path = calculatePathFromService(service);

		//Get path time
		Time timeOfDeparture = getTardiestReservationTime(service);
		if (timeOfDeparture < van.getNextTimeAvailable()) {
			timeOfDeparture = van.getNextTimeAvailable();
		}
		//cout << "Assigning times." << endl;
		double totalTime = assignTimeOfDeliverToReservations(path, service, timeOfDeparture);

		//Update van availability
		//cout << "Updating van information." << endl;
		Time endOfTripTime = timeOfDeparture.addSeconds(totalTime);
		van.setNextTimeAvailable(endOfTripTime);

		//Create the new service
		Service vanService(Van::getCapacity()-occupiedSeats, timeOfDeparture, service, path);
		van.addService(vanService);
		vans.insert(van);

		//cout << "Next Reservation." << endl << endl;
	}
}


void ServicesPlanner::planSingleVanMixingPassengers(){
	//preProcessEntryData();

	multiset<Van>::iterator van_it = vans.begin();
	Van van = *van_it;
	vans.erase(van_it);
	van.clearServices();
	while (!reservations.empty()) {
		// get first reservation
		Reservation seed = *reservations.begin();
		reservations.erase(reservations.begin());

		auto aux = reservations.begin();
		Position seedPosition = graph->findVertex(seed.getDest())->getPosition();

		vector<Reservation> toService;
		toService.push_back(seed);

		int numSlots = van.getCapacity()-seed.getNumPeople();
		
		// find reservations to mix
		while(numSlots > 0 && aux != reservations.end()){
			bool inTimeWindow = aux->getArrival() < (seed.getArrival() + Time(0, timeWindow,0));
			bool inRange = seedPosition.euclidianDistance((graph->findVertex(aux->getDest()))->getPosition() ) < maxDist;
			bool canFit = numSlots >= aux->getNumPeople();

			if (!inTimeWindow) break;

			if (inRange && canFit) {
				toService.push_back(*aux);
				numSlots -= aux->getNumPeople();
				aux = reservations.erase(aux);
				aux--;
			}
			aux++;
		}

		// path calculation
		set<Vertex*> vertexes;
		for_each(toService.begin(), toService.end(), [&vertexes, this](Reservation res) {
			vertexes.insert(graph->findVertex(res.getDest()));
		});
		vector<Edge> path = calculatePath(vertexes);

		// assign times of deliver
		Time timeOfDeparture = getTardiestReservationTime(toService);
		double totalTime = assignTimeOfDeliverToReservations(path, toService, timeOfDeparture);

		//Update van availability
		van.setNextTimeAvailable(timeOfDeparture.addSeconds(totalTime));

		// create new service
		Service vanService(numSlots,timeOfDeparture,toService,path);
		van.addService(vanService);
	}
	
	vans.insert(van);	
}

long int ServicesPlanner::objectiveFunction() {
	long int sum = 0;
	for (auto van : vans) {
		for (auto service : van.getServices()) {
			for (auto reservation : service.getReservations()) {
				sum += (reservation.getDeliver().toSeconds() - reservation.getArrival().toSeconds());
			}
		}
	}
	return sum;
}

void ServicesPlanner::integrateClientWithNoReservation(const Reservation & reservation, Time waitingTime) {

	// vans with services with vacant spots inside waitingTime window
	list<pair<Service*, Service*>> close;
	for (auto & van : vans)
		for (size_t s = 0 ; s < van.getServices().size(); s++) {
			Service & curr = van.getServices().at(s);
			int time_diff = curr.getStart().toSeconds() - reservation.getArrival().toSeconds();
			if (time_diff <= waitingTime.toSeconds() && time_diff >= 0 && curr.getVacant() >= reservation.getNumPeople()) {

				Service * next = (s == van.getServices().size()-1) ? nullptr : &van.getServices().at(s+1);
				if (next == nullptr) {
					newDestIntegration(reservation, curr);
					return;
				}

				close.push_back(pair<Service*, Service*>(&curr, next));
			}
		}

	// services that visit the reservation destination
	for (auto & service : close)
		for (auto & client : service.first->getReservations())
			if (reservation.getDest() == client.getDest()) {
				sameDestIntegration(reservation, *service.first);
				return;
			}

	// services which are not affected by new client addition
	for (auto & service : close) {

		// calculate time required to traverse path including new vertex
		set<Vertex *> vertices;
		for (auto reservation : service.first->getReservations())
			vertices.insert(graph->findVertex(reservation.getDest()));
		vertices.insert(graph->findVertex(reservation.getDest()));

		vector<Edge> path = calculatePath(vertices);
		int total = 0;
		for (auto edge : path) total += edge.getWeight();

		// if inserting this reservation does not affect next service
		if (service.first->getStart().toSeconds() + total <= service.second->getStart().toSeconds())
		{
			newDestIntegration(reservation, *service.first, path, total);
			return;
		}
	}
}

// must remove and re add services
// must remove and re add services
// must remove and re add services
// must remove and re add services
// must remove and re add services
// must remove and re add services
// must remove and re add services

void ServicesPlanner::sameDestIntegration(const Reservation & reservation, Service & service) {
	vector<Reservation> newReservations;
	bool added = false;
	int numPeople = 0;
	for (auto client : service.getReservations()) {
		newReservations.push_back(client);
		numPeople += client.getNumPeople();
		if (!added && reservation.getDest() == client.getDest()) {
			newReservations.push_back(reservation);
			added = true;
			numPeople += reservation.getNumPeople();
		}
	}

	if (added)  {
		service.setVacant(service.getVacant() - reservation.getNumPeople());
		service.setReservations(newReservations);
	}
}

void ServicesPlanner::newDestIntegration(const Reservation & reservation, Service & service) {

	set<Vertex *> vertices;
	for (auto reservation : service.getReservations())
		vertices.insert(graph->findVertex(reservation.getDest()));
	vertices.insert(graph->findVertex(reservation.getDest()));

	vector<Edge> path = calculatePath(vertices);
	int total = 0;
	for (auto edge : path) total += edge.getWeight();

	service.addReservation(reservation);
	service.setVacant(service.getVacant() - reservation.getNumPeople());
	service.setPath(path);
	service.setEnd(service.getStart().addSeconds(total));
}

void ServicesPlanner::newDestIntegration(const Reservation & reservation, Service & service, const vector<Edge> & path, int total) {
	service.addReservation(reservation);
	service.setVacant(service.getVacant() - reservation.getNumPeople());
	service.setPath(path);
	service.setEnd(service.getStart().addSeconds(total));
}

#include "Service.h"
#include "AirShuttle.h"

using namespace std;

Service::Service(Reservation * reservation, vector<Edge> & edges, Time lastEnd) {
	addReservation(reservation);
	this->vacant = VAN_CAPACITY - reservation->getNumPeople();
	double travel_time = 0;
	for (auto edge : edges) {
		travel_time += edge.getWeight();
		path.push_back(edge);
	}
	this->start = reservation->getArrival() < lastEnd ? lastEnd : reservation->getArrival();
	this->end = (this->start).addSeconds(travel_time);
}

int Service::getVacant() const {
	return vacant;
}

Time Service::getStart() const {
	return start;
}

Time Service::getEnd() const {
	return end;
}

vector<Reservation*> Service::getReservations() const {
	return reservations;
}

list<Edge> Service::getPath() const {
	return path;
}

void Service::addReservation(Reservation * res) {
	this->reservations.push_back(res);
}

void Service::addEdge(Edge edge) {
	this->path.push_back(edge);
}

void Service::addPath(const vector<Edge> & edges) {
	double travel_time = 0;
	for (auto edge: edges) {
		travel_time += edge.getWeight();
		path.push_back(edge);
	}
	this->end = (this->end).addSeconds(travel_time);
}

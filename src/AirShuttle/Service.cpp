#include "Service.h"
#include "AirShuttle.h"
#include <iostream>

using namespace std;

Service::Service(int vacant, Time start, std::vector<Reservation> reservations, std::vector<Edge> edges) {
	this->vacant = vacant;
	this->start = start;

	double totalWeight = 0;
	for (const Edge& e : edges) {
		totalWeight += e.getWeight();
	}
	this->end = start.addSeconds(totalWeight);

	this->reservations = reservations;
	this->path = edges;
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

const vector<Reservation>& Service::getReservations() const {
	return reservations;
}

const vector<Edge>& Service::getPath() const {
	return path;
}

void Service::setVacant(int vacant) {
	this->vacant = vacant;
}

void Service::setReservations(const std::vector<Reservation> &reservations) {
	this->reservations = reservations;
}

void Service::setPath(const std::vector<Edge> &edges) {
	this->path = edges;
}

void Service::setEnd(const Time & end) {
	this->end = end;
}


void Service::addReservation(const Reservation & reservation) {
	this->reservations.push_back(reservation);
}

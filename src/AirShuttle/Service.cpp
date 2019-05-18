#include "Service.h"

using namespace std;

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

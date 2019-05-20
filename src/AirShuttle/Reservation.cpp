#include "Reservation.h"

using namespace std;

Reservation::Reservation(string clientName, int NIF, int numPeople, Vertex * dest, Time arrival) {
	this->clientName = clientName;
	this->NIF = NIF;
	this->numPeople = numPeople;
	this->dest = dest;
	this->arrival = arrival;
}

string Reservation::getClientName() const {
	return clientName;
}

int Reservation::getNIF() const {
	return NIF;
}

int Reservation::getNumPeople() const {
	return numPeople;
}

Vertex* Reservation::getDest() const {
	return dest;
}

Time Reservation::getArrival() const {
	return arrival;
}

bool Reservation::operator<(const Reservation & reservation) const{
	return this->arrival < reservation.arrival;
}

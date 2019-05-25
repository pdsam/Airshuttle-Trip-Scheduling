#include "Reservation.h"

using namespace std;

Reservation::Reservation(string clientName, int NIF, int numPeople, int dest, Time arrival) {
	this->clientName = clientName;
	this->NIF = NIF;
	this->numPeople = numPeople;
	this->dest = dest;
	this->arrival = arrival;
	this->assigned = false;
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

int Reservation::getDest() const {
	return dest;
}

Time Reservation::getArrival() const {
	return arrival;
}

Time Reservation::getDeliver() const {
	return deliver;
}

void Reservation::setDeliver(const Time value) {
	this->deliver = value;
}

bool Reservation::operator<(const Reservation & reservation) const{
	return this->arrival < reservation.arrival;
}

bool Reservation::getAssigned() const {
	return assigned;
}
void Reservation::setAssigned(bool value) {
	this->assigned = value;
}


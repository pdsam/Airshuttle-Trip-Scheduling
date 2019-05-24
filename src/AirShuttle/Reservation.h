#ifndef RESERVATION_H_
#define RESERVATION_H_

#include <string>
#include "../Utils/Time.h"

class Reservation {
private:
	std::string clientName;
	int NIF;
	int numPeople;

	int dest;
	Time arrival, deliver;

public:
	Reservation(std::string clientName, int NIF, int numPeople, int dest, Time arrival);

	std::string getClientName() const;
	int getNIF() const;
	int getNumPeople() const;
	int getDest() const;
	Time getArrival() const;

	bool operator<(const Reservation & reservation) const;
};

#endif

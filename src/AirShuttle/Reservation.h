#ifndef RESERVATION_H_
#define RESERVATION_H_

#include <string>
#include "../Utils/Time.h"

class Reservation {
private:
	std::string clientName;
	int NIF;
	int numPeople;
	bool assigned = false;

	int dest;
	Time arrival, deliver;

	bool assigned;

public:
	Reservation(std::string clientName, int NIF, int numPeople, int dest, Time arrival);

	std::string getClientName() const;
	int getNIF() const;
	int getNumPeople() const;
	int getDest() const;
	Time getArrival() const;
	Time getDeliver() const;
	void setDeliver(const Time value);

	bool getAssigned() const;
	void setAssigned(bool value);

	bool getAssigned() const;
	bool operator<(const Reservation & reservation) const;
};

#endif

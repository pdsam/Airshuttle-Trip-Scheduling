#ifndef RESERVATION_H_
#define RESERVATION_H_

#include <string>
#include "../Utils/Time.h"
#include "../Graph/Vertex.h"

class Reservation {
private:
	std::string clientName;
	int NIF;
	int numPeople;

	Vertex * dest;
	Time arrival, deliver;

public:
	Reservation(std::string clientName, int NIF, int numPeople, Vertex * dest, Time arrival);

	std::string getClientName() const;
	int getNIF() const;
	int getNumPeople() const;
	Vertex* getDest() const;
	Time getArrival() const;

};

#endif

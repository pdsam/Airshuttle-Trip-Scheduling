#ifndef SERVICE_H_
#define SERVICE_H_

#include <vector>
#include <list>
#include "Reservation.h"
#include "../Utils/Time.h"
#include "../Graph/Edge.h"

class Service {
private:
	int vacant;
	Time start, end;
	std::vector<Reservation> reservations;
	std::list<Edge> path;

public:
	Service();

	int getVacant() const;
	Time getStart() const;
	Time getEnd() const;
	std::vector<Reservation> getReservations() const;
	std::list<Edge> getPath() const;

	void addReservation(Reservation res);
	void addEdge(Edge edge);

};

#endif

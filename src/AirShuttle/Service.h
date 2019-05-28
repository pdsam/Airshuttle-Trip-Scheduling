#ifndef SERVICE_H_
#define SERVICE_H_

#include <vector>
#include <list>
#include "../Utils/Time.h"
#include "../Graph/Edge.h"
#include "Reservation.h"

class Reservation;

class Service {
private:
	int vacant;
	Time start, end;
	std::vector<Reservation> reservations;
	std::vector<Edge> path;

public:
	Service(int vacant, Time start, std::vector<Reservation> reservations, std::vector<Edge> edges);

	int getVacant() const;
	Time getStart() const;
	Time getEnd() const;
	const std::vector<Reservation>& getReservations() const;
	const std::vector<Edge>& getPath() const;

	void setReservations(const std::vector<Reservation>& reservations);
	void setPath(const std::vector<Edge>& edges);
	void setEnd(const Time & end);
	void addReservation(const Reservation & reservation);

};

#endif

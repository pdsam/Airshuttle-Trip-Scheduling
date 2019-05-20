#ifndef SERVICES_PLANNER_H_
#define SERVICES_PLANNER_H_

#include <vector>
#include <set>
#include <string>
#include "Van.h"
#include "Reservation.h"
#include "../Graph/Graph.h"

class ServicesPlanner {
private:
	Graph * graph;
	Vertex * airport;
	std::vector<Van> vans;
	std::multiset<Reservation> reservations;
	int actionRadius, timeWindow, maxDist;

public:
	ServicesPlanner(Graph * graph, Vertex * airport, int actionRadius = 1, int timeWindow = 1, int maxDist = 1);

	Vertex * getAirport() const;
	std::vector<Van> getVans() const;
	std::multiset<Reservation> getReservations() const;

	void addVan(Van van);
	void addReservation(Reservation reservation);
	bool addReservationsFromFile(std::string location, std::string filename);

	void setActionRadius(int actionRadius);
	void setTimeWindow(int timeWindow);
	void setMaxDist(int maxDist);

	void preProcessEntryData();
	void planSingleVanNotMixingPassengers();
	void planSingleVanMixingPassengers();
	void planVansFleetMixingPassengers();


};


#endif

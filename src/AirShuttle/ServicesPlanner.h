#ifndef SERVICES_PLANNER_H_
#define SERVICES_PLANNER_H_

#include <vector>
#include <set>
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
	ServicesPlanner(Graph * graph, Vertex * airport, int actionRadius, int timeWindow, int maxDist);

	void addVan(Van van);
	void addReservation(Reservation reservation);

	void setActionRadius(int actionRadius);
	void setTimeWindow(int timeWindow);
	void setMaxDist(int maxDist);

	void preProcessGraph();
	void planSingleVanNotMixingPassengers();
	void planSingleVanMixingPassengers();
	void planVansFleetMixingPassengers();


};


#endif

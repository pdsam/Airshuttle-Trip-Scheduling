#ifndef SERVICES_PLANNER_H_
#define SERVICES_PLANNER_H_

#include <vector>
#include <set>
#include <string>
#include "Van.h"
#include "Reservation.h"
#include "AirShuttle.h"
#include "../Graph/Graph.h"

class ServicesPlanner {
private:
	Graph * graph;
	int airport;
	std::multiset<Van> vans;
	std::multiset<Reservation> reservations;
	int actionRadius, timeWindow, maxDist;

	void resetVans();
	std::vector<Edge> calculatePathFromService(const std::vector<Reservation> & service);
	int assignTimeOfArrivalToReservations(const std::vector<Edge> & path, std::vector<Reservation> & service, const Time & timeOfDeparture);
	std::vector<Reservation> mixClientsWithEarliest(const Reservation & earliest, const Van & van, int & occupiedSeats);

public:
	ServicesPlanner(Graph * graph, int airport, int vanCount, int actionRadius = ACTION_RADIUS, int timeWindow = TIME_WINDOW, int maxDist = MAX_DIST);

	Graph * getGraph() const;
	int getAirport() const;
	std::multiset<Van> getVans() const;
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

	
	std::vector<Edge> calculatePath(const std::set<Vertex*>& reservations);
	void planVansFleetMixingPassengers();
	int objectiveFunction();

};


#endif

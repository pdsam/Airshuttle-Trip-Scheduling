#include "ServicesPlanner.h"
#include "../Utils/utilities.c"

using namespace std;

ServicesPlanner::ServicesPlanner(Graph * graph, Vertex * airport, int actionRadius, int timeWindow, int maxDist) {
	this->graph = graph;
	this->airport = airport;
	this->actionRadius = max(actionRadius, 1);
	this->timeWindow = max(timeWindow, 1);
	this->maxDist = max(maxDist, 1);
}

void ServicesPlanner::addVan(Van van) {
	this->vans.push_back(van);
}

void ServicesPlanner::addReservation(Reservation reservation) {

    Reservation current = move(reservation);

    while (current.getNumPeople() > Van::getCapacity()) {
    	Reservation newRes(current.getClientName(), current.getNIF(), Van::getCapacity(),
    			current.getDest(), current.getArrival());

		current = Reservation(current.getClientName(), current.getNIF(), current.getNumPeople()-Van::getCapacity(),
				current.getDest(), current.getArrival());

    	reservations.insert(newRes);
    }

    reservations.insert(current);

}

void ServicesPlanner::setActionRadius(int actionRadius) {
	this->actionRadius = max(actionRadius, 1);
}

void ServicesPlanner::setTimeWindow(int timeWindow) {
	this->timeWindow = max(timeWindow, 1);
}

void ServicesPlanner::setMaxDist(int maxDist) {
	this->maxDist = max(maxDist, 1);
}

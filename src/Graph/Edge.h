#ifndef EDGE_H_
#define EDGE_H_

#include "../AirShuttle/AirShuttle.h"

class Vertex;

class Edge {
private:
	int id;
	Vertex * orig, * dest;
	double weight;
	double averageSpeed = VAN_SPEED;

public:
	Edge();
	Edge(int id, Vertex * orig, Vertex * dest, double weight);

	int getID() const;
	Vertex * getOrig() const;
	Vertex * getDest() const;
	double getWeight() const;
	double getAverageSpeed() const;
	double getDistance() const;

	void invertEdge();

	friend class Graph;
	friend class Vertex;
};

#endif

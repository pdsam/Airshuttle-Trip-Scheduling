#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"

class Vertex;

class Edge {
private:
	int id;
	Vertex * dest;
	double weight;

public:
	Edge(int id, Vertex * dest, double weight);

	int getID() const;
	Vertex * getDest() const;
	double getWeight() const;

	friend class Graph;
	friend class Vertex;
};

#endif

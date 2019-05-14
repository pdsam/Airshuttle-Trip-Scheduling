#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"

class Vertex;

class Edge {
private:
	Vertex * dest;
	double weight;

public:
	Edge(Vertex * dest, double weight);

	Vertex * getDest() const;
	double getWeight() const;

	friend class Graph;
	friend class Vertex;
};

#endif

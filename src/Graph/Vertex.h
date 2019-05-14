#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>
#include "Edge.h"
#include "../Utils/Position.h"

class Edge;

class Vertex {
private:
	int id;
	Position pos;
	std::vector<Edge> adj;

	void addEdge(Vertex * dest, double weight);

public:
	Vertex(int id, int x, int y);

	int getID() const;
	Position getPosition() const;

	friend class Graph;
};

#endif

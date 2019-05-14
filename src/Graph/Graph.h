#ifndef GRAPH_H_
#define GRAPH_H

#include <vector>

#include "Vertex.h"
#include "Edge.h"
#include "../Utils/Position.h"

class Graph {
private:
	std::vector<Vertex *> vertexSet;
public:
	Vertex *findVertex(const int &id) const;
	bool addVertex(const int &id, const Position & pos);
	bool addEdge(const int &id1, const int &id2);
	int getNumVertex() const;

	std::vector<Vertex *> getVertexSet() const;

};

#endif

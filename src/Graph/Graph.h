#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

#include "Vertex.h"
#include "Edge.h"

class Graph {
private:
	std::vector<Vertex *> vertexSet;
public:
	Vertex *findVertex(const int &id) const;
	bool addVertex(const int &id, int x, int y);
	bool addEdge(int id, int v_id1, int v_id2);
	int getNumVertex() const;

	std::vector<Vertex *> getVertexSet() const;

	void reset();
	~Graph();
};

#endif

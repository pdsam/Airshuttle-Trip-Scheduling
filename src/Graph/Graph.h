#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

#include "Vertex.h"
#include "Edge.h"
#include <algorithm>
#include "../Utils/MutablePriorityQueue.h"

#define INF std::numeric_limits<double>::max()

class Graph {
private:
	std::vector<Vertex *> vertexSet;

	void DFSVisit(Vertex * v);
public:
	Vertex *findVertex(const int &id) const;
	bool addVertex(const int &id, int x, int y);
	bool addEdge(int id, int v_id1, int v_id2);
	int getNumVertex() const;

	std::vector<Vertex *> getVertexSet() const;

	//single source algorithms
	Vertex * initSingleSource(const int &origin);
	bool relax(Vertex *v, Vertex *w, double weight);
	void dijkstraShortestPath(const int &source);
	vector<int> getPath(const int source, const int dest );


	void reset();
	~Graph();

	void DFSConnectivity(Vertex * start);
	void removeUnvisitedVertices();
};

#endif

#ifndef GRAPH_ALGORITHM_H_
#define GRAPH_ALGORITHM_H_

#include "../Graph/Graph.h"

class GraphAlgorithm {
protected:
	Graph * graph;

public:
	GraphAlgorithm(Graph * graph);

	virtual void execute(Vertex * start) = 0;

};

#endif

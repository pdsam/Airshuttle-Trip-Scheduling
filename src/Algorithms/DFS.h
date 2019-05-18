#ifndef DFS_H_
#define DFS_H_

#include "GraphAlgorithm.h"

class DFS : public GraphAlgorithm {

public:
	DFS(Graph * graph);

	virtual void execute(Vertex * start);
};

#endif

#ifndef GRAPH_LOADER_H_
#define GRAPH_LOADER_H_

#include <string>
#include "../Graph/Graph.h"

class GraphLoader {

private:

public:
	static bool loadGraph(std::string location, Graph * graph);
	static bool loadVertices(std::string location, Graph * graph);
	static bool loadEdges(std::string location, Graph * graph);
};


#endif

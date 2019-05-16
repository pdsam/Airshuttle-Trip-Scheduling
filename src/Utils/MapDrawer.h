#ifndef MAP_DRAWER_H_
#define MAP_DRAWER_H_

#include "../GraphViewer/cpp/graphviewer.h"
#include "../Graph/Graph.h"

class MapDrawer {
private:
	int width, height;
	GraphViewer * graphViewer;

	bool buildVerticesFromFile(std::string location);
	bool buildEdgesFromFile(std::string location);
	void resetGraphViewer();
public:
	MapDrawer(int width, int height);
	~MapDrawer();

	bool drawMapFromFile(std::string location);
	bool drawMapFromGraph(Graph * graph);
};


#endif

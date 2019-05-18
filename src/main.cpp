#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"

using namespace std;

int main() {

	Graph graph;
	GraphLoader::loadGraph("Porto", &graph);

	MapDrawer mapDrawer(2000, 2000);
	mapDrawer.drawMapFromGraph(&graph);
	getchar();

	return 0;
}
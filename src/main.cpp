#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"

using namespace std;

int main() {

	//Graph graph;
	//GraphLoader::loadGraph("Porto", &graph);
	//cout << graph.getNumVertex() << endl;

	MapDrawer mapDrawer(2000, 2000);
	mapDrawer.drawMapFromFile("Porto");
	getchar();
	mapDrawer.drawMapFromFile("Fafe");
	getchar();

	return 0;
}

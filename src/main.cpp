#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"

using namespace std;

int main() {

	Graph graph;
	GraphLoader::loadGraph("Porto", &graph);

	cout << graph.getNumVertex() << endl;

	return 0;
}

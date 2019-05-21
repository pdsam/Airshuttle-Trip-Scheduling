#include <fstream>
#include "GraphLoader.h"
#include "MapDrawer.h"

using namespace std;

bool GraphLoader::loadGraph(string location, Graph * graph) {

	//graph->reset();
	return (loadVertices(location, graph) && loadEdges(location, graph));// && loadTags(location, graph));
}

bool GraphLoader::loadVertices(string location, Graph * graph) {
	int n_nodes, id;
	double x, y;
	char c;

	ifstream ifs("maps/" + location + "/T06_nodes_X_Y_" + location + ".txt");
	if (!ifs.is_open()) return false;

	ifs >> n_nodes;

	for (int i = 0; i < n_nodes; i++) {
		ifs >> c >> id >> c >> x >> c >> y >> c;
		graph->addVertex(id, x, y);
	}

	ifs.close();
	return true;
}

bool GraphLoader::loadEdges(string location, Graph * graph) {
	int n_edges, id1, id2;
	char c;

	ifstream ifs("maps/" + location + "/T06_edges_" + location + ".txt");
	if (!ifs.is_open()) return false;

	ifs >> n_edges;

	for (int i = 0; i < n_edges; i++) {
		ifs >> c >> id1 >> c >> id2 >> c;
		graph->addEdge(i*2+1, id1, id2);
	}

	ifs.close();

	return true;
}

bool GraphLoader::loadTags(string location, Graph * graph) {
	int n_tags, n_of_tag, id;
	string tag;

	ifstream ifs("maps/" + location + "/T06_tags_" + location + ".txt");
	if (!ifs.is_open()) return false;

	ifs >> n_tags;

	for (int i = 0; i < n_tags; i++) {
		ifs >> tag >> n_of_tag;
		for (int j = 0; j < n_of_tag; j++) {
			ifs >> id;
			Vertex * v = graph->findVertex(id);
			if (v != nullptr) v->addTag(MapDrawer::getStringTag(tag));
		}
	}

	ifs.close();

	return true;
}


#include <cstdio>
#include <fstream>
#include <iostream>
#include "map_drawer.h"

using namespace std;

bool build_vertices(GraphViewer * gv, string location, int width, int height);
bool build_edges(GraphViewer * gv, string location);

GraphViewer* draw_map(string location, int width, int height) {

	GraphViewer * gv = new GraphViewer(width, height, false);
	gv->createWindow(width, height);
	gv->defineVertexSize(1);

	if (!build_vertices(gv, location, width, height) || !build_edges(gv, location)) {
		gv->closeWindow();
		delete gv;
		return NULL;
	}

	gv->rearrange();

	return gv;
}

bool build_vertices(GraphViewer * gv, string location, int width, int height) {
	int n_nodes, id, x_offset = 0, y_offset = 0;
	double x, y;
	char c;

	ifstream ifs("maps/" + location + "/T06_nodes_X_Y_" + location + ".txt");
	if (!ifs.is_open()) return false;

	ifs >> n_nodes;

	for (int i = 0; i < n_nodes; i++) {
		ifs >> c >> id >> c >> x >> c >> y >> c;
		if (i == 0) {
			x_offset = x + width/2;
			y_offset = y + height/2;
		}
		gv->addNode(id, x-x_offset, y-y_offset);
	}

	ifs.close();

	return true;
}

bool build_edges(GraphViewer * gv, string location) {
	int n_edges, id1, id2;
	char c;

	ifstream ifs("maps/" + location + "/T06_edges_" + location + ".txt");
	if (!ifs.is_open()) return false;

	ifs >> n_edges;

	for (int i = 0; i < n_edges; i++) {
		ifs >> c >> id1 >> c >> id2 >> c;
		gv->addEdge(i, id1, id2, EdgeType::DIRECTED);
	}

	ifs.close();

	return true;
}

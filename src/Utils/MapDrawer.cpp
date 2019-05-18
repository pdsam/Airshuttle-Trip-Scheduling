#include <iostream>
#include <cstdio>
#include <fstream>
#include <iostream>

#include "MapDrawer.h"

using namespace std;

MapDrawer::MapDrawer(int width, int height) {
	this->width = width;
	this->height = height;
	this->graphViewer = new GraphViewer(width, height, false);
}

MapDrawer::~MapDrawer() {
	delete graphViewer;
}

bool MapDrawer::drawMapFromFile(string location) {
	resetGraphViewer();
	graphViewer->createWindow(width, height);
	graphViewer->defineVertexSize(1);

	if (!buildVerticesFromFile(location) || !buildEdgesFromFile(location)) {
		graphViewer->closeWindow();
		return false;
	}

	graphViewer->rearrange();

	return true;
}

bool MapDrawer::buildVerticesFromFile(string location) {
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
		graphViewer->addNode(id, x-x_offset, y-y_offset);
	}

	ifs.close();

	return true;
}

bool MapDrawer::buildEdgesFromFile(string location) {
	int n_edges, id1, id2;
	char c;

	ifstream ifs("maps/" + location + "/T06_edges_" + location + ".txt");
	if (!ifs.is_open()) return false;

	ifs >> n_edges;

	for (int i = 0; i < n_edges; i++) {
		ifs >> c >> id1 >> c >> id2 >> c;
		graphViewer->addEdge(i, id1, id2, EdgeType::DIRECTED);
	}

	ifs.close();

	return true;
}

void MapDrawer::resetGraphViewer() {
	graphViewer->closeWindow();
	delete graphViewer;
	graphViewer = new GraphViewer(width, height, false);
}


bool MapDrawer::drawMapFromGraph(Graph * graph) {
	resetGraphViewer();
	graphViewer->createWindow(width, height);
	graphViewer->defineVertexSize(1);

	int x_offset = 0, y_offset = 0;
	if(graph->getNumVertex() > 0) {
		Position firstVPos = graph->getVertexSet().at(0)->getPosition();
		x_offset = firstVPos.getX();
		y_offset = firstVPos.getY();
	}
	for (Vertex * v : graph->getVertexSet()) {
		graphViewer->addNode(v->getID(), v->getPosition().getX() - x_offset, v->getPosition().getY() - y_offset);
		if (v->getTags().size() > 0) {
			if (v->getTags().size() > 1) cout << "more than 1 tag" << endl;
			graphViewer->setVertexColor(v->getID(), getTagColor(v->getTags().at(0)));
		}
	}

	for (Vertex * v : graph->getVertexSet()) {
		for (const Edge &e : v->getAdj()) {
			graphViewer->addEdge(e.getID(), v->getID(), e.getDest()->getID(), EdgeType::DIRECTED);
		}
	}

	graphViewer->rearrange();

	return true;
}

string MapDrawer::getTagColor(string tag) {
	if (tag == "aeroway=aerodrome") return BLUE;
	else if (tag == "aeroway=gate") return RED;
	else if (tag == "aeroway=terminal") return PINK;
	else if (tag == "aerodrome:type=*") return BLACK;
	else if (tag == "aeroway=heliport") return WHITE;
	else if (tag == "iata=*") return ORANGE;
	else if (tag == "landuse=military") return GREEN;
	return "";
}
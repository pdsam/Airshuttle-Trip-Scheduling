#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void exerciciotps()
{
	GraphViewer * gv = new GraphViewer(600,600,false);
	gv->createWindow(600,600);

	gv->addNode(0, 300, 50);
	gv->addNode(1, 318, 58);
	gv->addNode(2, 325, 75);
	gv->addNode(3, 318, 93);
	gv->addNode(4, 300, 100);
	gv->addNode(5, 282, 93);
	gv->addNode(6, 275, 75);
	gv->addNode(7, 282, 58);
	gv->addNode(8, 150, 200);
	gv->addNode(9, 300, 200);
	gv->addNode(10, 450, 200);
	gv->addNode(11, 300, 400);
	gv->addNode(12, 200, 550);
	gv->addNode(13, 400, 550);

	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);
	gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
	gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);

	gv->rearrange();

	Sleep(1000);

	gv->removeNode(12);
	gv->removeNode(13);

	gv->addNode(14, 250, 550);
	gv->addNode(15, 350, 550);
	gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
	gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);

	gv->rearrange();
}

void mapa_porto() {

	GraphViewer * gv = new GraphViewer(2000,2000, false);
	gv->createWindow(2000,2000);
	gv->defineVertexSize(1);

	ifstream ifs1("maps/Porto/T06_nodes_X_Y_Porto.txt");
	int n_nodes;
	ifs1 >> n_nodes;

	int id;
	double x, y;
	char c;
	int x_offset = 527000;
	int y_offset = 4555000;
	for (int i = 0; i < n_nodes; i++) {
		ifs1 >> c >> id >> c >> x >> c >> y >> c;
		gv->addNode(id, x-x_offset, y-y_offset);
	}

	ifs1.close();

	ifstream ifs2("maps/Porto/T06_edges_Porto.txt");
	int n_edges;
	ifs2 >> n_edges;

	int id1, id2;
	for (int i = 0; i < n_edges; i++) {
		ifs2 >> c >> id1 >> c >> id2 >> c;
		gv->addEdge(i, id1, id2, EdgeType::DIRECTED);
	}

	ifs2.close();

	gv->rearrange();
}


int main() {
	mapa_porto();
	getchar();
	return 0;
}

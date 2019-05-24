#include <iostream>
#include "Utils/GraphLoader.h"
#include "Graph/Graph.h"
#include "Utils/MapDrawer.h"
#include "AirShuttle/ServicesPlanner.h"
#include "AirShuttle/AirShuttle.h"
#include "Utils/MapTag.h"

using namespace std;

int main() {

	Graph graph;
	GraphLoader::loadGraph("Porto", &graph);

	ServicesPlanner planner(&graph, PORTO_AIRPORT, 1);
	planner.addReservationsFromFile("Porto", "reservations_1329449088.txt");

	graph.dijkstraShortestPath(PORTO_AIRPORT);

	vector<Vertex*> vertexes;
	vertexes.push_back(graph.findVertex(122432550));
	vertexes.push_back(graph.findVertex(408432564));
	vertexes.push_back(graph.findVertex(112594240));
	vertexes.push_back(graph.findVertex(343646784));

	vector<Edge> edges = planner.calculatePath(vertexes);
	cout << "Got path" << endl;

	//planner.planSingleVanNotMixingPassengers();

	MapDrawer mapDrawer(2000, 2000);
	//mapDrawer.drawMapFromPlannerSingleVan(&planner);
	GraphViewer* viewer = mapDrawer.getViewer();
	for (Edge edge: edges) {
		viewer->setEdgeThickness(edge.getID(), 20);
		viewer->setEdgeColor(edge.getID(), mapDrawer.getTagColor(EDGE_PATH));
		viewer->setVertexColor(edge.getDest()->getID(), mapDrawer.getTagColor(VERTEX_PATH));
	}

	getchar();

	return 0;
}

#include "Graph.h"

#include <iostream>
#include <unordered_set>

using namespace std;

Vertex* Graph::findVertex(const int &id) const {
	for (Vertex * v : vertexSet)
		if(v->id == id)
			return v;
	return nullptr;
}

bool Graph::addVertex(const int &id, int x, int y) {
	if (findVertex(id) != nullptr) return false;
	vertexSet.push_back(new Vertex(id, x, y));
	return true;
}

bool Graph::addEdge(int id, int v_id1, int v_id2) {
	Vertex * v1 = findVertex(v_id1);
	Vertex * v2 = findVertex(v_id2);
	if(v1 == nullptr || v2 == nullptr) return false;
	double dist = v1->pos.euclidianDistance(v2->pos);
	v1->addEdge(id, v2, dist);
	v2->addEdge(id+1, v1, dist);
	return true;
}

int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex*> Graph::getVertexSet() const {
	return vertexSet;
}

void Graph::reset() {
	for (size_t i = 0; i < vertexSet.size(); i++)
			delete vertexSet[i];
	vertexSet.clear();
}

Graph::~Graph() {
	for (size_t i = 0; i < vertexSet.size(); i++)
		delete vertexSet[i];
}

void Graph::DFSVisit(Vertex * v) {
	v->visited = true;
	// pre process
	v->addTag("DFS");
	for (const Edge & e : v->adj)
		if (!e.dest->visited)
			DFSVisit(e.dest);
	// post process
}

void Graph::DFSConnectivity(Vertex * start) {
	start->addTag("DFS start");
	for (Vertex * v : vertexSet)
		v->visited = false;
	DFSVisit(start);
}

void Graph::removeUnvisitedVertices() {
	unordered_set<Vertex*, VertexHash, VertexHash> removed;

	/* Remove vertices */
	vector<Vertex *>::iterator v_it;
	for (v_it = vertexSet.begin(); v_it != vertexSet.end(); v_it++) {
		if (!((*v_it)->visited)) {
			removed.insert(*v_it);
			v_it = vertexSet.erase(v_it);
			v_it--;
		}
	}

	/* Remove edges */
	vector<Edge>::iterator e_it;
	for (Vertex * v : vertexSet) {
		e_it = v->adj.begin();
		for (; e_it != v->adj.end(); e_it++) {
			if (removed.find((*e_it).dest) != removed.end()) {
				e_it = v->adj.erase(e_it);
				e_it--;
			}
		}
	}
}

/**********************SINGLE SOURCE ***********************/
Vertex * Graph::initSingleSource(const int &origin) {
	for(auto v : vertexSet) {
		v->distance = INF;
		v->path = nullptr;
	}
	auto s = findVertex(origin);
	s->distance = 0;
	return s;
}

inline bool Graph::relax(Vertex *v, Vertex *w, double weight) {
	if (v->distance + weight < w->distance) {
		w->distance = v->distance + weight;
		w->path = v;
		return true;
	}
	else
		return false;
}


//////////////A*//////////////////
double Graph::heuristic(Vertex * current, Vertex * dest){
	return dest->getPosition().euclidianDistance(current->getPosition()) ;
}

inline bool Graph::relax(Vertex *v, Vertex *w, double weight, Vertex * Dest, double averageSpeed){
	if (v->distance*averageSpeed + weight < w->distance) {
		w->distance = v->distance*averageSpeed + weight + heuristic(w,Dest);
		w->path = v;
		return true;
	}
	else
		return false;
}


void Graph::dijkstraShortestPath(const int &source){
	auto s = initSingleSource(source);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while( ! q.empty() ) {
		auto v = q.extractMin();
		for(auto e : v->adj) {
			auto oldDist = e.dest->distance;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
					q.insert(e.dest);
				else
					q.decreaseKey(e.dest);
			}
		}
	}
}
void Graph::AStar(const int &source, const int &des){
	auto s = initSingleSource(source);
	auto dest = this->findVertex(des);
	Vertex * previousVertex = nullptr;
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while(!q.empty() ){
		auto v = q.extractMin();
		v->path = previousVertex;
		previousVertex = v;
		if(dest->getID() == v->getID()){
			q.clear();
			continue;
		}
		for(auto e : v->adj) {
			e.dest->distance = heuristic(v,e.dest) + e.getDistance();
			q.insert(e.dest);
		}

	}

}


vector<int> Graph::getPath(const int source, const int dest ){
	vector<int> res;
	auto v = findVertex(dest);
	if (v == nullptr || v->distance == INF) // missing or disconnected
		return res;
	for ( ; v != nullptr; v = v->path)
		res.push_back(v->getID());
	reverse(res.begin(), res.end());
	return res;
}
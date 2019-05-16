#include "Vertex.h"

using namespace std;

Vertex::Vertex(int id, int x, int y) {
	this->id = id;
	this->pos = Position(x,y);
}

int Vertex::getID() const {
	return id;
}

Position Vertex::getPosition() const {
	return pos;
}

vector<Edge> Vertex::getAdj() const {
	return adj;
}

void Vertex::addEdge(int id, Vertex * dest, double weight) {
	adj.push_back(Edge(id, dest, weight));
}

void Vertex::addTag(std::string tag) {
	this->tags.push_back(tag);
}

vector<string> Vertex::getTags() const {
	return tags;
}


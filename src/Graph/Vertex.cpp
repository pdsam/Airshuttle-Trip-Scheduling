#include "Vertex.h"

Vertex::Vertex(int id, Position pos) {
	this->id = id;
	this->pos = pos;
}

int Vertex::getID() const {
	return id;
}

Position Vertex::getPosition() const {
	return pos;
}

void Vertex::addEdge(Vertex * dest, double weight) {
	adj.push_back(Edge(dest, weight));
}

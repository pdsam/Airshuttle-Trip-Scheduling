#include "Vertex.h"

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

void Vertex::addEdge(Vertex * dest, double weight) {
	adj.push_back(Edge(dest, weight));
}

void Vertex::addTag(std::string tag) {
	this->tags.push_back(tag);
}


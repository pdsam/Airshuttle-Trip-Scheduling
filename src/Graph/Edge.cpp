#include "Edge.h"
#include "Vertex.h"

Edge::Edge() {
	this->id = -1;
	this->dest = nullptr;
	this->weight = 0;
}

Edge::Edge(int id, Vertex* dest, double weight) {
	this->id = id;
	this->dest = dest;
	this->weight = weight;
}

int Edge::getID() const {
	return id;
}

Vertex* Edge::getDest() const {
	return dest;
}

double Edge::getWeight() const {
	return weight;
}




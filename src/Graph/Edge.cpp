#include "Edge.h"

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




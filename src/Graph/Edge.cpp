#include "Edge.h"

Edge::Edge(Vertex* dest, double weight) {
	this->dest = dest;
	this->weight = weight;
}

Vertex* Edge::getDest() const {
	return dest;
}

double Edge::getWeight() const {
	return weight;
}




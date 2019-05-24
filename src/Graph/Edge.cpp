#include "Edge.h"
#include "Vertex.h"

Edge::Edge() {
	this->id = -1;
	this->orig = nullptr;
	this->dest = nullptr;
	this->weight = 0;
}

Edge::Edge(int id, Vertex * orig, Vertex* dest, double weight) {
	this->id = id;
	this->orig = orig;
	this->dest = dest;
	this->weight = weight;
}

int Edge::getID() const {
	return id;
}

Vertex* Edge::getOrig() const {
	return orig;
}

Vertex* Edge::getDest() const {
	return dest;
}

double Edge::getWeight() const {
	return weight;
}

void Edge::invertEdge() {
	Vertex * temp = dest;
	dest = orig;
	orig = temp;
}

double Edge::getAverageSpeed() const{
	return averageSpeed;
}

double Edge::getDistance() const{
	return weight * averageSpeed*1000/3600;
}


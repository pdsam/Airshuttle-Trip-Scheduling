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

void Vertex::addTag(MapTag tag) {
	this->tags.push_back(tag);
}

vector<MapTag> Vertex::getTags() const {
	return tags;
}

double Vertex::getDistance(){return distance;}

bool Vertex::operator<(Vertex & vertex) const{
	return this->distance < vertex.getDistance();
}

#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>
#include "Edge.h"

class Vertex {
private:
	int id;
	double x, y;
	std::vector<Edge> adj;

public:
	Vertex(int id, double x, double y);

	int getID() const;
	double getX() const;
	double getY() const;

	friend class Graph;
};

#endif

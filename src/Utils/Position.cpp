#include <cmath>

#include "Position.h"

class Position {
private:
	double x, y;
public:
	Position(double x, double y);
	double getX() const;
	double getY() const;

	double euclidianDistance(const Position & p2);
};

Position::Position(double x, double y) {
	this->x = x;
	this->y = y;
}

double Position::getX() const {
	return x;
}

double Position::getY() const {
	return y;
}

double Position::euclidianDistance(const Position &p2) {
	return sqrt(pow(p2.x - x, 2) + pow(p2.y - y, 2));
}

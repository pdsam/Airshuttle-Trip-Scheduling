#ifndef UTILITIES_H_
#define UTILITIES_H_

class Position {
private:
	double x, y;
public:
	Position(double x, double y);
	double getX() const;
	double getY() const;

	double euclidianDistance(const Position & p2);
};

#endif

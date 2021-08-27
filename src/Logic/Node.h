#pragma once

#include "Point.h"
#include <vector>
#include <iostream>

enum class nodeType {
	WALKABLE,
	VISITED,
	WALL,
	START,
	END
};

class Node {
public:
	float f;
	float g;
	float h;

	Node(int x = 0, int y = 0) :type(nodeType::WALKABLE) {
		pos = Point(x, y);
		neighbors.reserve(8); //could have at most 8
		f = FLT_MAX;
		g = FLT_MAX;
		h = FLT_MAX;
	}

	void addNeighbor(int x, int y) {
		neighbors.push_back(Point(x, y));
	}
	void setPosition(int x, int y) {
		this->pos = Point(x, y);
	}
	void setType(nodeType nType) {
		this->type = nType;
	}

	Point getPos() const {
		return this->pos;
	}
	nodeType getType() const {
		return this->type;
	}

	const std::vector<Point>& getNeighbors() const {
		return this->neighbors;
	}

	bool operator ==(const Node& n) const { return this->pos == n.pos; }
	bool operator !=(const Node& n) const { return this->pos != n.pos; }

	bool operator <(const Node& n) const {
		return (this->f < n.f) ? true : false;
	}

	~Node() {}

private:
	Point pos;
	nodeType type;
	std::vector<Point> neighbors;
};
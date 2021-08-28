#pragma once

#include "Point.h"
#include <vector>
#include <iostream>

// A node class to store information about each node on the grid

// 5 types of nodes possible, only walls are not traversable
enum class nodeType {
	WALKABLE,
	VISITED,
	PATH,
	WALL,
	START,
	END
};

class Node {
public:
	//values needed for A* search
	Node* parent;

	float f;
	float g;
	float h;

	float dist;

	Node(int x = 0, int y = 0) :type(nodeType::WALKABLE),pos(Point(x,y)),f(FLT_MAX),g(FLT_MAX),h(FLT_MAX),dist(FLT_MAX) {
		neighbors.reserve(8); //could have at most 8 neighbors
		parent = nullptr;
	}

	void reset() {
		parent = nullptr;
		f = FLT_MAX;
		g = FLT_MAX;
		h = FLT_MAX;
		dist = FLT_MAX;
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

	~Node() {}

private:
	Point pos;
	nodeType type;
	std::vector<Point> neighbors;
};
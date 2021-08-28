#pragma once

#include "Search.h"

#include <queue>
#include "pq.h"

// compare for least dist as highest priority
class CompareNodeDist {
public:
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return rhs->dist < lhs->dist;
	}
};

class Dijkstra : public Search {
public:
	Dijkstra(Map* map);

	bool setup();
	void nextNodeStep();
	bool isNotFinished();
	void reset();
	~Dijkstra() {};
private:
	node_priority_queue<Node*, std::vector<Node*>, CompareNodeDist> exploredNodes;
};
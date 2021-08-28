#pragma once
#include <queue>
#include <iostream>

#include "Search.h"
#include "../Node.h"
#include "pq.h"

//compare function in priority queue to make node with least f the highest priority
struct CompareNodef{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return rhs->f < lhs->f;
	}
};

class ASearch : public Search {
public:
	ASearch(Map* map);

	bool setup();
	void nextNodeStep();
	bool isNotFinished();
	void reset();
	~ASearch() {};
private:
	node_priority_queue<Node*, std::vector<Node*>, CompareNodef> openList;
	float calculateH(Node*);
};
#pragma once
#include <stack>
#include "Search.h"

//searches iteratively, 
//actually recursively searches neighbor by neighbor
class IterativeSearch : public Search {
public:
	IterativeSearch(Map* map);
	bool setup();
	void nextNodeStep();
	bool isNotFinished();
	void reset();
private:
	bool contains(const Node*);
	std::vector<Node*> stack;
};
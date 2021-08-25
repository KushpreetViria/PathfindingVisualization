#pragma once
#include <stack>
#include "Search.h"

class IterativeSearch : public Search {
public:
	IterativeSearch(Map* map);
	bool setup();
	void nextNodeStep();
	bool isFinished();
	void reset();
private:
	std::stack<Node*, std::vector<Node*> > stack;
};
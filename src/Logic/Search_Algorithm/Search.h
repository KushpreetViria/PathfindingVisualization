#pragma once

#include "../Node.h"
#include "../Map.h"

//interface for what search algorithm implementations need
class Search {
public:
	virtual bool setup() = 0;
	virtual void nextNodeStep() = 0;
	virtual bool isNotFinished() = 0;
	virtual void reset() = 0;
	virtual ~Search() {};

	Node* currNode;
	Node* endNode;
	Map* myMap;
	bool foundEnd;
};
#pragma once

#include "../Node.h"
#include "../Map.h"

//interface for what search algorithm implementations need
class Search {
public:
	virtual bool setup() = 0;			//setup a new seach
	virtual void nextNodeStep() = 0;	//iterate once on the algorithm
	virtual bool isNotFinished() = 0;	//returns fals if algorithm is finished
	virtual void reset() = 0;			//resets the search, call this before setup when doing new search
	virtual ~Search() {};

	Node* currNode;
	Node* endNode;
	Map* myMap;
	bool foundEnd;
};
#pragma once
#include <queue>
#include "../Map.h"
#include "../Node.h"

class SearchAlgorithm
{
public:
	SearchAlgorithm() = delete;
	static bool simple_recursive_search(Map* map);
	static bool a_search(Map* map);
	static bool djisktra_search(Map* map);
private:
	static int maxStackSize;
	static Node* mapEndNode; 
	static Map* searchMap;

	static bool searchNode(Node* currNode, int stackDepth = 0);
};
#include "SearchAlgorithm.h"

int SearchAlgorithm::maxStackSize = 1024;
Node* SearchAlgorithm::mapEndNode = nullptr;
Map* SearchAlgorithm::searchMap = nullptr;


bool SearchAlgorithm::searchNode(Node* currNode, int stackDepth) {
	bool returnVal = false;

	if (*currNode == *SearchAlgorithm::mapEndNode) {
		return true;
	}	
	
	if(currNode->getType() != nodeType::START)
		currNode->setType(nodeType::VISITED);

	if (stackDepth >= SearchAlgorithm::maxStackSize) {
		return false;
	}
	
	for (auto it = std::begin(currNode->getNeighbors()); it != std::end(currNode->getNeighbors()); ++it) {
		Node* neighbor = &searchMap->getNodes()[it->x][it->y];
		if (neighbor->getType() != nodeType::VISITED && neighbor->getType() != nodeType::WALL &&
			neighbor->getType() != nodeType::START) {
			bool returnVal = searchNode(neighbor,  stackDepth+1);
			if (returnVal) return true;
		}
	}
	return false;
}

bool SearchAlgorithm::simple_recursive_search(Map* map) {
	bool found = false;
	Node* startNode = map->getStart();
	Node* endNode = map->getEnd();
	if (startNode != nullptr && endNode != nullptr) {
		try {
			SearchAlgorithm::maxStackSize = 1024;
			SearchAlgorithm::mapEndNode = endNode;
			SearchAlgorithm::searchMap = map;

			found = searchNode(startNode);
		}catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	return found;
}
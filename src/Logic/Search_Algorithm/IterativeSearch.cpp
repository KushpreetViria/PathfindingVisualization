#include "IterativeSearch.h"

IterativeSearch::IterativeSearch(Map* map)
{
	Node* currNode = nullptr;
	Node* endNode = nullptr;
	bool foundEnd = false;
	myMap = map;
}

bool IterativeSearch::setup() {
	if (myMap->getStart() != nullptr && myMap->getEnd() != nullptr) {
		foundEnd = false;
		currNode = myMap->getStart();
		endNode = myMap->getEnd();
		stack.push(currNode);
		return true;
	}
	return false;
}

bool IterativeSearch::isNotFinished() {
	return stack.size() > 0 && !foundEnd;
}

void IterativeSearch::reset() {
	currNode = nullptr;
	endNode = nullptr;
	foundEnd = false;
	while (!stack.empty()) { stack.pop(); }
}

void IterativeSearch::nextNodeStep() {
	Node* node = stack.top();
	stack.pop();
	if (*node == *endNode) {
		foundEnd = true;
	}else {
		if (node->getType() != nodeType::START) node->setType(nodeType::VISITED);
		for (auto it = std::begin(node->getNeighbors()); it != std::end(node->getNeighbors()); ++it) {
			Node* neighbor = &myMap->getNodes()[it->y][it->x];
			if (neighbor->getType() != nodeType::VISITED && neighbor->getType() != nodeType::WALL &&
				neighbor->getType() != nodeType::START) {
				stack.push(neighbor);
			}
		}
	}
}
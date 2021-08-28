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
		myMap->resetNodes();
		foundEnd = false;
		currNode = myMap->getStart();
		endNode = myMap->getEnd();
		stack.push_back(currNode);					//start with the starting node in the stack
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
	while (!stack.empty()) { stack.pop_back(); }
}

void IterativeSearch::nextNodeStep() {
	Node* node = stack.back();
	stack.pop_back();
	if (*node == *endNode) {						//if we found end node, we are done
		foundEnd = true;
	}else {
		if (node->getType() != nodeType::START) node->setType(nodeType::VISITED);						//visist the current node
		for (auto it = std::begin(node->getNeighbors()); it != std::end(node->getNeighbors()); ++it) {
			Node* neighbor = &myMap->getNodes()[it->y][it->x];
			if (neighbor->getType() != nodeType::VISITED && neighbor->getType() != nodeType::WALL &&	//for each unvisited neighbor
				neighbor->getType() != nodeType::START) {
				if (!contains(neighbor)) {
					stack.push_back(neighbor);										// push it onto the stack if its new
					neighbor->parent = node;
				}
			}
		}
	}
}

bool IterativeSearch::contains(const Node* node) {
	auto it = std::find_if(stack.begin(), stack.end(), [&node](const Node* x) { return *x == *node; });
	return it != stack.end();
}
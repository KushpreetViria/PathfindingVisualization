#include "pch.h"
#include "Dijkstra.h"

Dijkstra::Dijkstra(Map* map)
{
	currNode = nullptr;
	endNode = nullptr;
	foundEnd = false;
	myMap = map;
}

bool Dijkstra::setup()
{
	if (myMap->getStart() != nullptr && myMap->getEnd() != nullptr) {
		myMap->resetNodes();

		foundEnd = false;
		currNode = myMap->getStart();
		currNode->dist = 0.0f;								//set starting node distance to 0
		endNode = myMap->getEnd();

		exploredNodes.push(currNode);						//push starting node to the queue
		return true;
	}
    return false;
}

void Dijkstra::nextNodeStep()
{
	Node* current = exploredNodes.top();
	exploredNodes.pop();

	if (*current == *endNode) {															//if current is end node, we are done
		foundEnd = true;
	}else {
		if (current->getType() != nodeType::START) current->setType(nodeType::VISITED);	//viist the current node

		auto neighbors = current->getNeighbors();
		for (auto it = std::begin(neighbors); it != std::end(neighbors); ++it) {
			Node* neighbor = &myMap->getNodes()[it->y][it->x];
			nodeType type = neighbor->getType();
			if (type != nodeType::WALL && type != nodeType::START &&					//for each unvisited neighbor
				type != nodeType::VISITED){
				float newDist = current->dist + 1;
				if (newDist < neighbor->dist) {											//if its a smaller path update neighbor
					neighbor->parent = current;
					neighbor->dist = newDist;
					if (!exploredNodes.find(neighbor)) {								// add this unvisited neighbor to the queue if it's new
						exploredNodes.push(neighbor);
					}
				}			
			}
		}
	}
}

bool Dijkstra::isNotFinished()
{
	return !exploredNodes.empty() && !foundEnd;
}

void Dijkstra::reset()
{
	currNode = nullptr;
	endNode = nullptr;
	foundEnd = false;

	while (!exploredNodes.empty()) { exploredNodes.pop(); }
}

#include "ASearch.h"
#include <assert.h>

ASearch::ASearch(Map* map) {
	currNode = nullptr;
	endNode = nullptr;
	foundEnd = false;
	myMap = map;
}

bool ASearch::setup()
{
	if (myMap->getStart() != nullptr && myMap->getEnd() != nullptr) {
		foundEnd = false;
		currNode = myMap->getStart();
		endNode = myMap->getEnd();

		size_t rows = myMap->getHeight();
		size_t cols = myMap->getWidth();
		
		currNode->g = 0;
		currNode->h = calculateH(currNode);
		currNode->f = currNode->g + currNode->h;

		openList.push(currNode); //push the starting node

		return true;
	}
	return false;
}



void ASearch::nextNodeStep(){	
	Node* current = openList.top();
	openList.pop();

	std::cout << openList.size() << std::endl;

	if (*current == *endNode) {
		std::cout << "found destination" << std::endl;
		foundEnd = true;		
	}else {
		//dont want to color the start node with visited... but for everything else yes
		if (current->getType() != nodeType::START) current->setType(nodeType::VISITED);

		auto neighbors = current->getNeighbors();
		for (auto it = std::begin(neighbors); it != std::end(neighbors); ++it) {
			Node* neighbor = &myMap->getNodes()[it->y][it->x];
			nodeType type = neighbor->getType();
			if ( (type != nodeType::WALL) && (type != nodeType::START) && type != nodeType::VISITED) {
				
				float costg = current->g + 1; //cost to move from current to neighbor
				float costh = calculateH(neighbor); //cost to move from current to neighbor
				float costf = costg + costh;

				if (openList.find(neighbor)) {
					if (costg > neighbor->g)
						continue;
				}else {
					neighbor->g = costg;
					neighbor->h = costh;
					neighbor->f = costf;
					openList.push(neighbor);
				}				
			}
		}
	}
}

bool ASearch::isNotFinished()
{
	return !openList.empty() && !foundEnd;
}

void ASearch::reset()
{
	currNode = nullptr;
	endNode = nullptr;
	foundEnd = false;
	
	while (!openList.empty()) { openList.pop(); }
}

float ASearch::calculateH(Node* curr) {
	int curr_row = curr->getPos().y;
	int curr_col = curr->getPos().x;

	int end_row = endNode->getPos().y;
	int end_col = endNode->getPos().x;


	return sqrt((curr_col - end_col) * (curr_col - end_col) + (curr_row - end_row) * (curr_row - end_row));
	//return abs(curr_row - end_row) + abs(curr_col - end_col)
}
#include "ASearch.h"

ASearch::ASearch(Map* map) {
	currNode = nullptr;
	endNode = nullptr;
	foundEnd = false;
	myMap = map;

}

//initial setup before starting search
bool ASearch::setup()
{
	if (myMap->getStart() != nullptr && myMap->getEnd() != nullptr) {
		myMap->resetNodes();						//reset g,h and f in all nodes
		
		foundEnd = false;
		currNode = myMap->getStart();
		endNode = myMap->getEnd();
		
		currNode->g = 0;							//calculate starting node g, h and f
		currNode->h = calculateH(currNode);
		currNode->f = currNode->g + currNode->h;

		openList.push(currNode);					//push the starting node onto the open list

		return true;
	}
	return false;
}


//visist the next node in the A* search
void ASearch::nextNodeStep(){	
	Node* current = openList.top();																			//pop the node with the least f in openList
	openList.pop();

	if (*current == *endNode) {																				// we found the end node
		foundEnd = true;		
	}else {
		if (current->getType() != nodeType::START) current->setType(nodeType::VISITED);						//"visit" this current node, dont want to draw over start nodes however

		auto neighbors = current->getNeighbors();
		for (auto it = std::begin(neighbors); it != std::end(neighbors); ++it) {							// for all neighbors
			Node* neighbor = &myMap->getNodes()[it->y][it->x];
			nodeType type = neighbor->getType();
			if ( (type != nodeType::WALL) && (type != nodeType::START) && type != nodeType::VISITED) {		//if its a valid neighbor that has not been visited yet
				
				float costg = current->g + 1;																//cost to move from current node to this neighbor			

				if (openList.find(neighbor)) {																//if this is longer then a previous path, ignore this neighbor
					if (costg > neighbor->g)
						continue;
					else {
						neighbor->parent = current;
					}
				}else {																						//otherwise set g,h and f and insert into openList
					float costh = calculateH(neighbor); //cost to move from current to neighbor
					float costf = costg + costh;

					neighbor->g = costg;
					neighbor->h = costh;
					neighbor->f = costf;
					openList.push(neighbor);
					neighbor->parent = current;
				}				
			}
		}
	}
}

//is the search finished?
bool ASearch::isNotFinished()
{
	return !openList.empty() && !foundEnd;
}

// call this before doing a new search
void ASearch::reset()
{
	currNode = nullptr;
	endNode = nullptr;
	foundEnd = false;
	
	while (!openList.empty()) { openList.pop(); }
}

//a helper function to calculate heuristic value based on diagonal distance to the goal from current node
float ASearch::calculateH(Node* curr) {
	int curr_row = curr->getPos().y;
	int curr_col = curr->getPos().x;

	int end_row = endNode->getPos().y;
	int end_col = endNode->getPos().x;


	return (float)sqrt((curr_col - end_col) * (curr_col - end_col) + (curr_row - end_row) * (curr_row - end_row));
}
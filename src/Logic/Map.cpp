#include "Map.h"
#include <iostream>

constexpr auto DEFAULT_WIDTH = 10;
constexpr auto DEFAULT_HEIGHT = 10;

char defaultMap[DEFAULT_WIDTH][DEFAULT_HEIGHT] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','O','E','X','O','O','X','S','O','X' },
	{ 'X','O','X','X','O','O','X','O','O','X' },
	{ 'X','O','X','X','O','O','X','O','O','X' },
	{ 'X','O','X','X','X','O','X','O','O','X' },
	{ 'X','O','X','O','X','O','X','O','O','X' },
	{ 'X','O','X','O','X','O','X','O','O','X' },
	{ 'X','O','X','O','X','O','X','O','O','X' },
	{ 'X','O','O','O','O','O','O','O','O','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};

//creates a default map of nodes
Map::Map()
{
	this->width = DEFAULT_WIDTH;
	this->height = DEFAULT_HEIGHT;
	currStartNode = nullptr;
	currEndNode = nullptr;

	myNodes = new Node*[height];
	for (int i = 0; i < height; i++) {
		myNodes[i] = new Node[width];
	}

	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			Node* currNode = &myNodes[r][c];
			currNode->setPosition(c, r);
			addNeighbors(r, c);
			switch (defaultMap[r][c]) {
			case 'O':				
				currNode->setType(nodeType::WALKABLE);
				break;
			case 'X':
				currNode->setType(nodeType::WALL);
				break;
			case 'S':
				currNode->setType(nodeType::START);
				currStartNode = currNode;
				break;
			case 'E':
				currNode->setType(nodeType::END);
				currEndNode = currNode;
				break;
			}
		}
	}
}

//creates a custum map with just walkable nodes
Map::Map(int width, int height)
{
	if (width > 100) width = 100;
	if (height > 100) height = 100;
	this->width = width;
	this->height = height;
	currStartNode = nullptr;
	currEndNode = nullptr;

	myNodes = new Node*[height];
	for (int i = 0; i < height; i++) {
		myNodes[i] = new Node[width];
	}
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			Node* currNode = &myNodes[r][c];
			currNode->setPosition(c,r);
			addNeighbors(r, c);
		}
	}
}

// resets the g,h and f values in all nodes to maximum float
void Map::resetNodes() {
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			Node* currNode = &myNodes[r][c];
			currNode->reset();
		}
	}
}

//resets the map overall, 
//changes all nodes to walkable if hard is passed as true
// other wise changes visited and path nodes
void Map::reset(bool hard)
{
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			Node* currNode = &myNodes[r][c];
			currNode->reset(); //reset search variables

			nodeType type = currNode->getType();
			if ((type == nodeType::VISITED) || (type == nodeType::PATH) || (hard && type == nodeType::WALL)) {
				currNode->setType(nodeType::WALKABLE);
			}
		}
	}
}

//follow the parent nodes set to color the path from endnode to startnode
void Map::colorPath() {
	colorParent(currEndNode);
}

void Map::colorParent(Node* curr) {
	if (curr->getType() != nodeType::END && curr->getType() != nodeType::START) {
		curr->setType(nodeType::PATH);
	}
	if (curr->parent != nullptr) colorParent(curr->parent);
}

//adds the neighbors of the node at position row and col in the Node 2d array
void Map::addNeighbors(unsigned int row, unsigned int col) {
	Node* currNode = &myNodes[row][col];
	
	if (inRange(row - 1, col + 0)) currNode->addNeighbor(col, row - 1);
	if (inRange(row + 0, col - 1)) currNode->addNeighbor(col - 1, row);
	if (inRange(row + 1, col + 0)) currNode->addNeighbor(col, row + 1);
	if (inRange(row + 0, col + 1)) currNode->addNeighbor(col + 1,row);		
	if (inRange(row + 1, col + 1)) currNode->addNeighbor(col + 1, row + 1);
	if (inRange(row - 1, col - 1)) currNode->addNeighbor(col - 1, row - 1);
	if (inRange(row - 1, col + 1)) currNode->addNeighbor(col + 1, row - 1);
	if (inRange(row + 1, col - 1)) currNode->addNeighbor(col - 1, row + 1);
}

bool Map::inRange(int row, int col) {
	return ((row >= 0 && row < this->height) && (col >= 0 && col < this->width));
}

void Map::printMap() {
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			std::cout << "[" << myNodes[r][c].getPos().x << "," << myNodes[r][c].getPos().y << "]";
		}
		std::cout << std::endl;
	}
}

int Map::getWidth() const {
	return width;
}

int Map::getHeight() const {
	return height;
}

Node* Map::getStart()
{
	return currStartNode;
}

Node* Map::getEnd()
{
	return currEndNode;
}

Node** Map::getNodes() {
	return myNodes;
}


// updates the start node of the map, removes the previous one if it succeeded
void Map::updateStartNode(Node* node)
{
	if (node != nullptr && node->getType() == nodeType::START) {
		if(currStartNode != nullptr && *node != *currStartNode) currStartNode->setType(nodeType::WALKABLE);
		this->currStartNode = node;
	}
}

//upadates the end node of the map, removes the previous one if it suceeded
void Map::updateEndNode(Node* node)
{
	if (node != nullptr && node->getType() == nodeType::END) {
		if (currEndNode!= nullptr && *node != *currEndNode) currEndNode->setType(nodeType::WALKABLE);
		this->currEndNode = node;
	}
}

Map::~Map()
{
	for (size_t r = 0; r < height; r++) {		
		delete[] myNodes[r];
	}
	delete[] myNodes;
}

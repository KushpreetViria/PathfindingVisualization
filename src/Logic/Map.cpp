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

Map::Map(int width, int height)
{
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

void Map::addNeighbors(unsigned int row, unsigned int col) {
	Node* currNode = &myNodes[row][col];
	
	if (inRange(row + 0, col + 1)) currNode->addNeighbor(row ,col + 1);
	if (inRange(row + 0, col - 1)) currNode->addNeighbor(row ,col - 1);
	if (inRange(row + 1, col + 1)) currNode->addNeighbor(row + 1, col);
	if (inRange(row - 1, col + 1)) currNode->addNeighbor(row - 1, col);
	if (inRange(row + 1, col + 1)) currNode->addNeighbor(row + 1,col + 1);
	if (inRange(row - 1, col - 1)) currNode->addNeighbor(row - 1,col - 1);
	if (inRange(row - 1, col + 1)) currNode->addNeighbor(row - 1,col + 1);
	if (inRange(row + 1, col - 1)) currNode->addNeighbor(row + 1,col - 1);
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

	/*for (auto it = std::begin(myNodes[0][0].getNeighbors()); it != std::end(myNodes[0][0].getNeighbors()); ++it) {
		std::cout << "Neighbor: " << it->x << ", " << it->y << "\n";
	}*/
}

int Map::getWidth() const {
	return width;
}

int Map::getHeight() const {
	return height;
}

Node** Map::getNodes() {
	return myNodes;
}

void Map::updateStartNode(Node* node)
{
	if (node != nullptr && node->getType() == nodeType::START) {
		if(currStartNode != nullptr && *node != *currStartNode) currStartNode->setType(nodeType::WALKABLE);
		this->currStartNode = node;
	}
}

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

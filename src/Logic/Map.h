#pragma once

#include "Node.h"

class Map
{
private:
	Node** myNodes;
	int width;
	int height;

	Node* currStartNode;
	Node* currEndNode;

	void addNeighbors(unsigned int  row, unsigned int col);
	bool inRange(int row, int col);
public:
	Map(); //default
	Map(int width, int height); //custom
	void reset(bool hard);

	int getWidth() const;
	int getHeight() const;
	Node* getStart();
	Node* getEnd();
	Node** getNodes();

	void updateStartNode(Node* node);
	void updateEndNode(Node* node);

	void printMap();
	~Map();
};


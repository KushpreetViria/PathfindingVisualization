#pragma once

#include "Node.h"

class Map
{
private:
	Node** myNodes;
	int width;
	int height;

	void addNeighbors(unsigned int  row, unsigned int col);
	bool inRange(int row, int col);
public:
	Map(); //default
	Map(int width, int height); //custom

	int getWidth() const;
	int getHeight() const;
	Node** getNodes();

	void printMap();
	~Map();


};

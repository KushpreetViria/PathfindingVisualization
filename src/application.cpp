#include "pch.h"

#include <iostream>

#include "Graphics/Graphics.h"
#include "Logic/Map.h"

int main(int argc, char** argv) {

	//to change the algorithm, set it in the start key handle in graphics.cpp

	Map* newWorld = new Map(50, 50);
	//Map* newWorld = new Map();
	Graphics graphics = Graphics(newWorld);
	if (!graphics.initialize()) {
		std::cerr << "Error: Failed to initialize graphics. Exiting..." << std::endl;
		return EXIT_FAILURE;
	}
	graphics.run();
	delete newWorld;
	return EXIT_SUCCESS;
}
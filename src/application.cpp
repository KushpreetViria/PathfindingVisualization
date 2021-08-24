#include "pch.h"

#include <iostream>

#include "Graphics/Graphics.h"
#include "Logic/Map.h"

int main(int argc, char** argv) {
	Map* newWorld = new Map(25, 25);
	Graphics graphics = Graphics(newWorld);
	if (!graphics.initialize()) {
		std::cerr << "Error: Failed to initialize graphics. Exiting..." << std::endl;
		return EXIT_FAILURE;
	}
	graphics.run();
	//engine.setAlgo();
	//engine.setMap();
	delete newWorld;
	return EXIT_SUCCESS;
}
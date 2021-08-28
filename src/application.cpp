#include "pch.h"

#include <iostream>

#include "Graphics/Graphics.h"
#include "Logic/Map.h"

int main(int argc, char** argv) {
	
	Map* newWorld = new Map(50, 50);
	Graphics graphics = Graphics(newWorld);
	if (!graphics.initialize()) {
		std::cerr << "Error: Failed to initialize graphics. Exiting..." << std::endl;
		return EXIT_FAILURE;
	}
	graphics.run();
	delete newWorld;
	return EXIT_SUCCESS;
}
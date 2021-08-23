#include "pch.h"

#include <iostream>

#include "Graphics/Graphics.h"
#include "Logic/Map.h"

int main(int argc, char** argv) {
	Graphics graphics = Graphics();
	if (!graphics.initialize()) {
		std::cerr << "Error: Failed to initialize graphics. Exiting..." << std::endl;
		return EXIT_FAILURE;
	}
	graphics.run();
	//engine.setAlgo();
	//engine.setMap();
	return EXIT_SUCCESS;
}
#pragma once
#include <queue>
#include <stack>
#include <iostream>

#include "../Map.h"
#include "../Node.h"

#include "Search.h"
#include "IterativeSearch.h"
#include "ASearch.h"
#include "Dijkstra.h"

constexpr auto NUM_OF_ALGORITHMS = 3;

enum class algorithms {
	ITERATIVE,
	A_STAR,
	DJIKSTRA
};
const algorithms algoArray[NUM_OF_ALGORITHMS] = { algorithms::ITERATIVE,algorithms::A_STAR,algorithms::DJIKSTRA};

//for printing the enum values
static std::ostream& operator<<(std::ostream& out, const algorithms value) {
	auto returnVal = "";
	switch (value) {

	case algorithms::ITERATIVE:
		returnVal = "ITERATIVE";
		break;
	case algorithms::A_STAR:
		returnVal = "A_STAR";
		break;
	case algorithms::DJIKSTRA:
		returnVal = "DJIKSTRA";
		break;
	}

	return out << returnVal;
}

//A class to handle calls to the search algorithms.
//It starts, resets, iterates the algorithms
class SearchAlgorithm{
public:
	SearchAlgorithm(Map* map, algorithms algo = algorithms::ITERATIVE) { 
		Started = false;
		myMap = map;
		search = nullptr;
		changeAlgorithm(algo);
	}

	void changeAlgorithm(algorithms alg) {
		if (search != nullptr) delete search; //delete the preious one
		
		currentAlgorithm = alg;

		switch (currentAlgorithm) {
			case algorithms::ITERATIVE:
				search = new IterativeSearch(myMap);
				break;
			case algorithms::A_STAR:
				search = new ASearch(myMap);
				break;
			case algorithms::DJIKSTRA:
				search = new Dijkstra(myMap);
				break;
			}
	}
	
	void setupSearch() {
		search->reset();
		Started = search->setup();
	};

	void updateNextStep() {
		if(Started) search->nextNodeStep();
	};

	bool searchNotFinished() {
		bool result = search->isNotFinished();
		if (!result) {
			if (search->foundEnd) { 
				std::cout << "Found destination" << std::endl; 
				myMap->colorPath();								//color the path if found destination
			}
			else std::cout << "Failed to find Destination" << std::endl;
			search->reset();
			Started = false;
		}
		return result;
	}

	void resetSearch() {
		search->reset();
		Started = false;
	}

	bool hasSearchStarted() {
		return Started;
	}

	~SearchAlgorithm() {
		if (search != nullptr) delete search;
	}
private:
	bool Started;
	Search* search;
	Map* myMap;
	algorithms currentAlgorithm;
};
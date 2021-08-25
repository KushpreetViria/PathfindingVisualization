#pragma once
#include <queue>
#include <stack>
#include "../Map.h"
#include "../Node.h"
#include "Search.h"
#include "IterativeSearch.h"

enum class algorithms {
	ITERATIVE,
	A_STAR,
	DJIKSTRA
};

class SearchAlgorithm
{
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
				break;
			case algorithms::DJIKSTRA:
				break;
			}
	}
	
	void setupSearch() {
		Started = search->setup();
	};

	void updateNextStep() {
		if(Started) search->nextNodeStep();
	};

	bool searchNotFinished() {
		bool result = search->isFinished();
		if (!result) {
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
	algorithms currentAlgorithm;
	Search* search;
	Map* myMap;
};
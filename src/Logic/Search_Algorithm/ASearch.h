#pragma once
#include <queue>
#include <iostream>

#include "Search.h"
#include "../Node.h"

//inheriting the standard library priority queue, maybe a bad idea

struct CompareNode{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return *rhs < *lhs;
	}
};

template<typename T, typename Sequence = std::vector<T>, typename Compare = std::less<typename Sequence::value_type> >
	class node_priority_queue : public std::priority_queue<T, Sequence, Compare> {
public:
	bool remove(const T& value) {
		if (value == nullptr) return false;
		auto it = std::find_if( this->c.begin(), this->c.end(),[&value](const T& x) { return *x == *value; });
		if (it != this->c.end()) {
			this->c.erase(it);
			std::make_heap(this->c.begin(), this->c.end(), this->comp);
			return true;
		}
		else {
			return false;
		}
	}

	bool find(const T& value) {
		if (value == nullptr) return false;
		auto it = std::find_if(this->c.begin(), this->c.end(), [&value](const T& x) { return *x == *value; });
		return it != this->c.end();
	}
};

class ASearch : public Search {
public:
	ASearch(Map* map);

	bool setup();
	void nextNodeStep();
	bool isNotFinished();
	void reset();
	~ASearch() {};
private:
	node_priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
	float calculateH(Node*);
};
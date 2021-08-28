#pragma once

#include <queue>

//a priority queue of nodes implemented in the standard libary
//inherit it, and add a few extra methods that are useful
template<
	typename T,
	typename Sequence = std::vector<T>,
	typename Compare = std::less<typename Sequence::value_type>>

	class node_priority_queue : public std::priority_queue<T, Sequence, Compare> {
	public:
		bool remove(const T& value) {
			if (value == nullptr) return false;
			auto it = std::find_if(this->c.begin(), this->c.end(), [&value](const T& x) { return *x == *value; });
			if (it != this->c.end()) {
				this->c.erase(it);
				_STD make_heap(this->c.begin(), this->c.end(), this->comp);
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

		void forceSortByDist() {
			auto func = [](const T& lhs, const T& rhs) {return lhs->dist < rhs->dist; };
			std::sort(this->c.begin(), this->c.end(), func);
		}
};

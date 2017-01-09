#pragma once

#include <vector>
#include <memory>
#include <queue>
#include "Raster.hpp"
#include <climits>

using std::vector;
using std::shared_ptr;
using std::priority_queue;
using std::pair;

template<typename T, typename priority_t>
struct PriorityQueue {
	typedef pair<priority_t, T> PQElement;
	priority_queue<PQElement, vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const { return elements.empty(); }

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	inline T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

class AlgorithmBase
{
  public:
	typedef pair<int, int> intPair;
	const intPair nullPair = intPair(INT_MAX,INT_MAX);
	AlgorithmBase(Raster* raster_);
	~AlgorithmBase();
	void shortestPath(const intPair& from, const intPair& to) {};
	void printPath(const intPair& begin, const intPair& from);
	vector<intPair> getPath();
	void clearParent();

  protected:
	intPair **parent;	//2D array with hashes
	Raster* raster;
};



class AlgorithmWithPriorityQueue : public AlgorithmBase
{
  public:
	using AlgorithmBase::intPair;

	AlgorithmWithPriorityQueue(Raster* raster_);
	~AlgorithmWithPriorityQueue();

  protected:
	int** distance;	//priorities for queue
};

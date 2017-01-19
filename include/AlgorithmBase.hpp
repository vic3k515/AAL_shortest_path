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
	typedef Raster::Location Location;
	const Location nullPair = Location(INT_MAX,INT_MAX);
	AlgorithmBase(Raster* raster_);
	~AlgorithmBase();
	void shortestPath(const Location& from, const Location& to) {};
	vector<Location> getPath();

  protected:
	Location **parent;	//2D array of Location
	Raster* raster;
};



class AlgorithmWithPriorityQueue : public AlgorithmBase
{
  public:
	using AlgorithmBase::Location;

	AlgorithmWithPriorityQueue(Raster* raster_);
	~AlgorithmWithPriorityQueue();

  protected:
	int** distance;	//priorities for queue
};

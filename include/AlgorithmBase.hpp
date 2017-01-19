/**
 * Finding shortest path between points on square grid.
 *
 * @file AlgorithmBase.hpp
 * @brief Declarations of base classes for path-finding algorithms.
 * @author Wiktor Franus
 */

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

/**
 * Custom priority queue based on std::priority_queue.
 * Element with the lowest priority is at the top.
 */
template<typename T, typename priority_t>
struct PriorityQueue {
	typedef pair<priority_t, T> Element;
	priority_queue<Element, vector<Element>,
		std::greater<Element>> elements;

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

/**
 * Base class for path-finding algorithm.
 */
class AlgorithmBase
{
  public:
	typedef Raster::Location Location;
	const Location nullPair = Location(INT_MAX,INT_MAX);

	/**
	 * Constructor that sets raster for algorithm to grid
	 * pointed by raster_.
	 * @param raster_ pointer to grid
	 */
	AlgorithmBase(Raster* raster_);
	/**
	 * AlgorithmBase destructor.
	 */
	~AlgorithmBase();

	/**
	 * Finds shortest path between two locations on raster.
	 * @param from Start point
	 * @param to End point
	 */
	void shortestPath(const Location& from, const Location& to) {};
	/**
	 * Returns shortest path found by the algorithm.
	 * @return Vector of Locations composing shortest path
	 * found by algorithm.
	 */
	vector<Location> getPath();

  protected:
  	/* 2d array containg parent Locations of i,jth element */
	Location **parent;
	/* Pointer to grid algorithm will be run on */
	Raster* raster;
};


/**
 * Base class for path-finding algorithm based on
 * priority queue. It holds additional distance
 * matrix describing distance of i,j martix elem
 * from starting point.
 */
class AlgorithmWithPriorityQueue : public AlgorithmBase
{
  public:
	using AlgorithmBase::Location;

	AlgorithmWithPriorityQueue(Raster* raster_);
	~AlgorithmWithPriorityQueue();

  protected:
	int** distance;	//priorities for queue
};

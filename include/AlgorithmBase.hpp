#pragma once

#include <vector>
#include <memory>
#include <queue>
#include "Raster.hpp"
#include <climits>

using std::vector;
using std::shared_ptr;
using std::priority_queue;

class AlgorithmBase
{
  public:
	typedef std::pair<int, int> intPair;
	AlgorithmBase(Raster* raster_);
	~AlgorithmBase();
	void shortestPath(const intPair& from, const intPair& to) {};
	void printPath(const intPair& begin, const intPair& from);

  protected:
	inline int hash_(int i, int j) {return i + j*(raster->getWidth());};
	inline intPair unhash_(int hash) {return std::make_pair(hash%(raster->getWidth()), hash / (raster->getWidth()));};
	int **parent;	//2D array with hashes
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

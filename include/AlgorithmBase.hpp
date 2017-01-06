#ifndef ALGORITHM_BASE_HPP
#define ALGORITHM_BASE_HPP
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
	AlgorithmBase(shared_ptr<Raster> raster_) :
		raster(raster_),
		parent(raster_->width * raster_->height, -INT_MAX) {};
	~AlgorithmBase() {};
	void shortestPath(const intPair& from, const intPair& to);
	void printPath(const intPair& begin, const intPair& from);

  protected:
	inline int hash_(int i, int j) {return i*(raster->height) +j;};
	inline intPair unhash_(int hash) {return std::make_pair(hash/(raster->height), hash%(raster->width));};
	vector<int> parent;
	shared_ptr<Raster> raster;
};



class AlgorithmWithPriorityQueue : public AlgorithmBase
{
	using AlgorithmBase::intPair;

  public:
	AlgorithmWithPriorityQueue(shared_ptr<Raster> raster_) : AlgorithmBase(raster_) {}
	~AlgorithmWithPriorityQueue() {};

  private:
	vector<int> distance;
};

#endif

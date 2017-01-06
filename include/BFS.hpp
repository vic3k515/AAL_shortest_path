#include "AlgorithmBase.hpp"

using std::queue;

class BFS : public AlgorithmBase
{
public:
	using Location=AlgorithmBase::intPair;
	BFS(shared_ptr<Raster> raster_) : AlgorithmBase(raster_) {};
	~BFS() {};

	void shortestPath(const intPair& from, const intPair& to)
	{
		queue<Location> queue;
		queue.push(from);

		int fromHash = hash_(from.first, from.second);
		parent[fromHash] = fromHash;

		while (!queue.empty())
		{
			auto current = queue.front();
			queue.pop();
			//std::cout << current.first << current.second << std::endl;

			if (current.first == to.first && current.second == to.second)
			{
				AlgorithmBase::printPath(from, to);
			}

			for (auto next : raster->neighbors(current))
			{
			  if (parent[hash_(next.first, next.second)] == -INT_MAX)
			  {
				  queue.push(next);
				  parent[hash_(next.first, next.second)] = hash_(current.first, current.second);
			  }
			}
		}
	}
};

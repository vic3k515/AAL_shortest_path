#include "AlgorithmBase.hpp"

using std::queue;

class BFS : public AlgorithmBase
{
public:
	using Location=AlgorithmBase::intPair;
	BFS(Raster* raster_) : AlgorithmBase(raster_) {};
	~BFS() {};

	void shortestPath(const intPair& from, const intPair& to)
	{
		queue<Location> queue;
		queue.push(from);

		int fromHash = hash_(from.first, from.second);
		parent[from.first][from.second] = fromHash;

		while (!queue.empty())
		{
			auto current = queue.front();
			queue.pop();
			//std::cout << current.first << current.second << std::endl;

			if (current.first == to.first && current.second == to.second)
			{
				AlgorithmBase::printPath(from, to);
			}

			for (auto next : raster->neighbours(current))
			{
				//std::cout << "dupa" << std::endl;
			  if (parent[next.first][next.second] == INT_MAX)
			  {
				  queue.push(next);
				  parent[next.first][next.second] = hash_(current.first, current.second);
			  }
			}
		}
	}
};

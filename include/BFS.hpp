#include "AlgorithmBase.hpp"

using std::queue;

class BFS : public AlgorithmBase
{
public:
	BFS(Raster* raster_) : AlgorithmBase(raster_) {};
	~BFS() {};

	void shortestPath(const Location& from, const Location& to)
	{
		queue<Location> queue;
		queue.emplace(from);
		parent[from.first][from.second] = from;

		while (!queue.empty())
		{
			auto current = queue.front();
			queue.pop();

			if (current == to)
				break;

			for (auto next : raster->neighbours(current))
			{
			  if (parent[next.first][next.second] == nullPair)
			  {
				  queue.emplace(next);
				  parent[next.first][next.second] = current;
			  }
			}
		}
	}
};

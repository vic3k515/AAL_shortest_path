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
		queue.emplace(from);
		parent[from.first][from.second] = from;

		while (!queue.empty())
		{
			auto current = queue.front();
			queue.pop();

			if (current == to)
			{
				//AlgorithmBase::printPath(from, to);
				break;
			}

			for (auto next : raster->neighbours(current))
			{
			  if (parent[next.first][next.second] == nullPair)
			  {
				  queue.emplace(next);
				 //std::cout << temp << " c: (" << current.first << "," << current.second << ") "  << " c_un: (" << temp1.first << "," << temp1.second << ") "
					// << raster->getVal(temp1) << " n: (" << next.first << "," << next.second << ") " << raster->getVal(next) << std::endl;
				  parent[next.first][next.second] = current;
			  }
			}
		}
	}
};

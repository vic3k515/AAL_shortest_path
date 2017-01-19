/**
 * Finding shortest path between points on square grid.
 *
 * @file BFS.hpp
 * @brief Implementation of Breadth First Search path-finding algorithm.
 * @author Wiktor Franus
 */

#include "AlgorithmBase.hpp"

using std::queue;

class BFS : public AlgorithmBase
{
public:
	/**
	 * Constructor that calls AlgorithmBase constructor.
	 * @param raster_ pointer to grid
	 */
	BFS(Raster* raster_) : AlgorithmBase(raster_) {};
	/**
	 * Default destructor.
	 */
	~BFS() {};

	/**
	 * Finds shortest path between two locations on raster.
	 * @param from Start point
	 * @param to End point
	 */
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

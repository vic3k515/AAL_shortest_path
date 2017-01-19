/**
 * Finding shortest path between points on square grid.
 *
 * @file Dijkstra.hpp
 * @brief Implementation of Dijkstra path-finding algorithm.
 * @author Wiktor Franus
 */

#pragma once
#include "AlgorithmBase.hpp"

class Dijkstra : public AlgorithmWithPriorityQueue
{
  public:
 	/**
	 * Constructor that calls AlgorithmWithPriorityQueue constructor.
	 * @param raster_ pointer to grid
	 */
	Dijkstra(Raster* raster_) : AlgorithmWithPriorityQueue(raster_) {};
	/**
	 * Default destructor.
	 */
	~Dijkstra() {};

	/**
	 * Finds shortest path between two locations on raster.
	 * @param from Start point
	 * @param to End point
	 */
	void shortestPath(const Location& from, const Location& to)
	{
		PriorityQueue<Location, int> priorQueue;
		parent[from.first][from.second] = from;
		distance[from.first][from.second] = 0;
		priorQueue.put(from, 0);

		while (!priorQueue.empty())
		{
			auto current = priorQueue.get();

			if (current == to)
				break;

			for (auto next : raster->neighbours(current))
			{
				int new_cost = distance[current.first][current.second] + 1;
				if (new_cost < distance[next.first][next.second])
				{
					distance[next.first][next.second] = new_cost;
					parent[next.first][next.second] = current;
					priorQueue.put(next, new_cost);
				}
			}
		}
	}
};

#pragma once
#include "AlgorithmBase.hpp"

class A_star : public AlgorithmWithPriorityQueue
{
public:
	A_star(Raster* raster_) : AlgorithmWithPriorityQueue(raster_) {};
	~A_star() {};

	inline double heuristic(intPair a, intPair b) {
		return abs(a.first - b.first) + abs(a.second - b.second);
	}

	void shortestPath(const intPair& from, const intPair& to)
	{
		PriorityQueue<intPair, int> priorQueue;
		parent[from.first][from.second] = from;
		distance[from.first][from.second] = 0;
		priorQueue.put(from, 0);

		while (!priorQueue.empty())
		{
			auto current = priorQueue.get();

			if (current == to)
			{
				//AlgorithmBase::printPath(from, to);
				break;
			}

			for (auto next : raster->neighbours(current))
			{
				int new_cost = distance[current.first][current.second] + 1;
				if (new_cost < distance[next.first][next.second])
				{
					distance[next.first][next.second] = new_cost;
					parent[next.first][next.second] = current;
					int new_prio = new_cost + heuristic(next, to);
					priorQueue.put(next, new_prio);
				}
			}
		}
	}
};

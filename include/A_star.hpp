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
		auto cmp = [](intPair left, intPair right) {return left.second > right.second; };
		std::priority_queue<intPair, vector<intPair>, decltype(cmp)> priorQueue(cmp);

		int fromHash = hash_(from.first, from.second);
		parent[from.first][from.second] = fromHash;
		distance[from.first][from.second] = 0;
		priorQueue.emplace(fromHash, 0);

		while (!priorQueue.empty())
		{
			int minIndex = priorQueue.top().first;
			auto current = std::make_pair(unhash_(minIndex).first, unhash_(minIndex).second);

			priorQueue.pop();

			if (current.first == to.first && current.second == to.second)
			{
				AlgorithmBase::printPath(from, to);
			}

			for (auto next : raster->neighbours(current))
			{

				int new_cost = distance[current.first][current.second] + 1;
				if (new_cost < distance[next.first][next.second])
				{
					distance[next.first][next.second] = new_cost;
					parent[next.first][next.second] = hash_(current.first, current.second);
					int new_prio = new_cost + heuristic(next, to);
					priorQueue.emplace(hash_(next.first, next.second), new_prio);
				}
			}
		}
	}
};

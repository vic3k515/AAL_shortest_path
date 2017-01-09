#include "../include/AlgorithmBase.hpp"
#include <iostream>

AlgorithmBase::AlgorithmBase(Raster* raster_) : raster(raster_)
{
	parent = new intPair*[raster->getHeight()];
	for (int i = 0; i < raster->getHeight(); ++i)
	{
		parent[i] = new intPair[raster->getWidth()];
		std::fill(parent[i], parent[i] + raster->getWidth(), intPair(INT_MAX,INT_MAX));
	}

}

AlgorithmBase::~AlgorithmBase()
{
	for (int i = 0; i < raster->getHeight(); ++i)
		delete[] parent[i];
	delete[] parent;
}

void AlgorithmBase::printPath(const intPair& begin, const intPair& from)
{
	int count = 0;
	intPair curr = from;
	while(curr != begin)
	{
		std::cout << "(" << curr.first << "," << curr.second << ") -> ";
		curr = parent[curr.first][curr.second];
		++count;
	}
	std::cout << "(" << begin.first << "," << begin.second << ")" << std::endl;
	std::cout << " Length = " << count << std::endl;
}

vector<AlgorithmBase::intPair> AlgorithmBase::getPath()
{
	vector<intPair> path;
	intPair current = raster->getEnd();
	//path.push_back(current); // not included for drawing (end already drown)
	while (current != raster->getStart()) {
		path.push_back(current);
		current = parent[current.first][current.second];
	}
	//path.push_back(raster->getStart()); // optional
	//std::reverse(path.begin(), path.end()); // not necessary for drawing
	return path;
	
}

AlgorithmWithPriorityQueue::AlgorithmWithPriorityQueue(Raster * raster_) : AlgorithmBase(raster_)
{
	distance = new int*[raster->getHeight()];
	for (int i = 0; i < raster->getHeight(); ++i)
	{
		distance[i] = new int[raster->getWidth()];
		std::fill(distance[i], distance[i] + raster->getWidth(), INT_MAX);
	}
}

AlgorithmWithPriorityQueue::~AlgorithmWithPriorityQueue()
{
	for (int i = 0; i < raster->getHeight(); ++i)
		delete[] distance[i];
	delete[] distance;
}

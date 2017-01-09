#include "../include/AlgorithmBase.hpp"
#include <iostream>

AlgorithmBase::AlgorithmBase(Raster* raster_) : raster(raster_)
{
	parent = new int*[raster->getHeight()];
	for (int i = 0; i < raster->getHeight(); ++i)
	{
		parent[i] = new int[raster->getWidth()];
		std::fill(parent[i], parent[i] + raster->getWidth(), INT_MAX);
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
	//for (int i = 0; i < raster->height; ++i)
	//{
	//	for (int j = 0; j < raster->width; ++j) {
	//		if (parent[i][j] != -INT_MAX)
	//			std::cout << parent[i][j];
	//		else
	//			std::cout << "  ";
	//		std::cout << " ";
	//	}
	//	std::cout << std::endl;
	//}

	int count = 0;
	intPair curr = from;
	while(curr != begin)
	{
		std::cout << "(" << curr.first << "," << curr.second << ") -> ";
		//curr = unhash_(parent[hash_(curr.first, curr.second)]);
		curr = unhash_(parent[curr.first][curr.second]);
		++count;
	}
	std::cout << "(" << begin.first << "," << begin.second << ")" << std::endl;
	std::cout << " Length = " << count << std::endl;
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

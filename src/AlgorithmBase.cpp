#include "../include/AlgorithmBase.hpp"
#include <iostream>

void AlgorithmBase::printPath(const intPair& begin, const intPair& from)
{
	intPair curr = from;
	while(curr != begin)
	{
		std::cout << "(" << curr.first << "," << curr.second << ") -> ";
		curr = unhash_(parent[hash_(curr.first, curr.second)]);
	}
	std::cout << "(" << begin.first << "," << begin.second << ")" << std::endl;
}

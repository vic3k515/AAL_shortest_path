//#include "../include/Raster.hpp"
#include "../include/BFS.hpp"
#include <iostream>
#include <memory>

std::array<Raster::Location, 4> Raster::DIRS  {std::make_pair(1, 0), std::make_pair(0, -1),
										 std::make_pair(-1, 0), std::make_pair(0, 1)};

int main()
{
	int width, height;
	std::cin >> width >> height;
	std::shared_ptr<Raster> ptr(new Raster(width,height));
	BFS bfs(ptr);
	const std::pair<int,int> start = std::make_pair(3,0);
	const std::pair<int,int> end = std::make_pair(7,8);

	std::cout << "Start: " << start.first << ", " << start.second << std::endl;
	std::cout << "End: " << end.first << ", " << end.second << std::endl;
	std::cout << "Shortest path (inversed): " << std::endl;
	bfs.shortestPath(start, end);
	return 0;
}

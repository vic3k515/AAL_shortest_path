//#include "../include/Raster.hpp"
#include "../include/BFS.hpp"
#include "../include/Dijkstra.hpp"
#include "../include/A_star.hpp"
#include <iostream>
#include <memory>
#include <chrono>

using namespace std;
using namespace std::chrono;

std::array<Raster::Location, 4> Raster::DIRS  {make_pair(1, 0), make_pair(0, -1),
										 make_pair(-1, 0), make_pair(0, 1)};

void printParent(int **parent, int height, int width) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j)
			if (parent[i][j] == INT_MAX)
				std::cout << "M" << " ";
			else if (parent[i][j] >= width*height)
				std::cout << "@" << " ";
			else
				std::cout << parent[i][j] << " ";;
		std::cout << std::endl;
	}
}

int main()
{
	int width, height;
	cin >> width >> height;
	Raster* rptr = new Raster(width,height, false);
	rptr->generateGrid(1,1);
	rptr->draw();
	BFS bfs(rptr);
	A_star a_star(rptr);
	Dijkstra dijkstra(rptr);
	const std::pair<int, int> start = rptr->getStart();
	const std::pair<int, int> end = rptr->getEnd();

	high_resolution_clock::time_point t1, t2;

	cout << "Start: " << start.first << ", " << start.second << endl;
	cout << "End: " << end.first << ", " << end.second << endl;

	///* A* */
	//cout << "Shortest path A_star(inversed): " << endl;
	//t1 = high_resolution_clock::now();
	//a_star.shortestPath(start, end);
	//t2 = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(t2 - t1).count();
	//cout << "A* exec time: " << duration << endl;

	/* BFS */
	cout << "Shortest path BFS(inversed): " << endl;
	t1= high_resolution_clock::now();
	bfs.shortestPath(start, end);
	t2 = high_resolution_clock::now();
	 auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "BFS exec time: " << duration << endl;



	///* Dijkstra*/
	//cout << "Shortest path Dijkstra(inversed): " << endl;
	//t1 = high_resolution_clock::now();
	//dijkstra.shortestPath(start, end);
	//t2 = high_resolution_clock::now();
	//duration = duration_cast<microseconds>(t2 - t1).count();
	//cout << "Dijkstra exec time: " << duration << endl;


	
	delete rptr;
	return 0;
}

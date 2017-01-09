#include "../include/BFS.hpp"
#include "../include/draw.hpp"
#include <chrono>

using namespace std;
using namespace chrono;

const int multipliers[] = {1,2,4,6,8,10,20,30,40,50,100,500, 1000};

int main()
{
	int width, height;
	cin >> width >> height;
	Raster* rptr = new Raster(width, height, false);
	BFS bfs(rptr);

	high_resolution_clock::time_point t1, t2;
	vector<pair<int, int>> path;

	cout << "BFS exec time: " << endl;
	for (auto m : multipliers)
	{
		rptr->generateGrid(10*m, 10*m);
		t1 = high_resolution_clock::now();
		bfs.shortestPath(rptr->getStart(), rptr->getEnd());
		t2 = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(t2 - t1).count();
		cout << "m: " << m << " " << duration << endl;
		path = bfs.getPath();
		bfs.clearParent();
		rptr->clear();
	}

	//draw result from last iteration
	drawResult(width, height, rptr, path);

	return 0;
}
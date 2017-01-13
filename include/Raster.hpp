#pragma once

#include <array>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <chrono>
#include <random>
#include <functional>
#include <algorithm>

using std::vector;
using std::array;

class Raster
{
public:
	typedef std::pair<int, int> Location;
	static array<Location, 4> DIRS;

	Raster(int width_, int height_);
	~Raster();

	//inlines
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	Location getStart() const { return start; }
	Location getEnd() const { return end; }
	int getVal(Location id) { return grid[id.first][id.second]; }
	bool is_valid(Location id) const
	{
		int x = id.first;
		int y = id.second;
		return 0 <= x && x < height && 0 <= y && y < width && grid[x][y] == 1;
	}
	bool is_wall(Location id) const
	{
		int x = id.first;
		int y = id.second;
		return 0 <= x && x < height && 0 <= y && y < width && grid[x][y] == 0;
	}

	bool readStartAndEnd();
	bool readGrid();
	void generateGrid(int& vertices, int& edges);
	void draw();
	void clear();
	void neighbors2(Location curTile, vector<int>& moves, int field_width);
	void createMaze(Location start_point, int& vertices, int& edges);
	int countNewEdges(Location loc);
	vector<Location> neighbours(Location id) const;

private:
	Location start = {0, 0}, end = {0, 0};
	int width, height;
	int **grid; //2D int array
};

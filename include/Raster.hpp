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

	Raster(int width_, int height_, bool from_cin = false);
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
		return 0 <= x && x < height && 0 <= y && y < width && grid[x][y] != 0;
	}
	bool is_wall(Location id) const
	{
		int x = id.first;
		int y = id.second;
		return 0 <= x && x < height && 0 <= y && y < width && grid[x][y] != 1;
	}

	vector<Location> neighbours(Location id) const;
	void createMaze(int start_x, int start_y, int v, int e);
	void generateGrid(int vertices, int edges);
	void draw();
	void clear();

	void neighbors2(Location curTile, vector<int>& moves, int field_width = 2);
	void createMaze2(Location start_point, int vertices, int edges);

private:
	Location start = {0, 0}, end = {0, 0};
	int width, height;
	int **grid; //2D int array
};

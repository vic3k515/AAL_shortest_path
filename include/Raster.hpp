#ifndef RASTER_HPP
#define RASTER_HPP
#include <array>
#include <vector>
#include <iostream>

using std::vector;
using std::array;

struct Raster
{
	typedef std::pair<int, int> Location;
	static array<Location, 4> DIRS;
	int width, height;
	//unordered_set<Location> walls;
	int **grid; //2D int array


	Raster(int width_, int height_) : width(width_), height(height_)
	{
		grid = new int*[height_];
		for (int i = 0; i < height_; ++i)
			grid[i] = new int[width_]();

		for (int i =0; i < height_; ++i)
			for (int j =0; j < width_; ++j) {
				std::cin >> grid[i][j];
			}
	}

	~Raster()
	{
		for (int i = 0; i < height; ++i)
			delete[] grid[i];
		delete[] grid;
	}

	inline bool is_valid(Location id) const
	{
		int x = id.first;
		int y = id.second;
		return 0 <= x && x < width && 0 <= y && y < height && grid[x][y] != 0;
	}

	vector<Location> neighbors(Location id) const
	{
		int x, y, dx, dy;
		x = id.first;
		y = id.second;
		vector<Location> results;

		for (auto dir : DIRS) {
			dx = dir.first;
			dy = dir.second;
			Location next(x + dx, y + dy);
			//if (in_bounds(next) && passable(next)) {
			if (is_valid(next)) {
				results.push_back(next);
			}
		}

		return results;
	}
};

#endif

/**
 * Finding shortest path between points on square grid.
 *
 * @file Raster.cpp
 * @brief Definition of class representing square grid.
 * @author Wiktor Franus
 */

#include "../include/Raster.hpp"
#include <iostream>

// initialize static member
array<Raster::Location, 4> Raster::DIRS{ std::make_pair(1, 0), std::make_pair(-1, 0),
										 std::make_pair(0, -1), std::make_pair(0, 1) };

Raster::Raster(int width_, int height_) : width(width_), height(height_)
{
	grid = new int*[height_];
	for (int i = 0; i < height_; ++i)
		grid[i] = new int[width_](); //initializes grid with 0s (walls)
}

Raster::Raster(const Raster& other) : width(other.width), height(other.height)
{
	grid = new int*[height];
	for (int i = 0; i < height; ++i)
	{
		grid[i] = new int[width];
		for(int j=0; j<width; ++j)
			grid[i][j] = other.grid[i][j];
	}
}

Raster::~Raster()
{
	for (int i = 0; i < height; ++i)
		delete[] grid[i];
	delete[] grid;
}

bool Raster::is_valid(Location id) const
{
	int x = id.first;
	int y = id.second;
	return 0 <= x && x < height && 0 <= y && y < width && grid[x][y] == 1;
}
bool Raster::is_wall(Location id) const
{
	int x = id.first;
	int y = id.second;
	return 0 <= x && x < height && 0 <= y && y < width && grid[x][y] == 0;
}

void Raster::findMoves(Location curTile, vector<int>& moves, int step)
{
	int counter_down = 0, counter_up = 0, counter_left = 0, counter_right = 0;

	for(int i = 1; i <= step; ++i)
	{
		if (is_wall(Location(curTile.first + i, curTile.second)))
			++counter_down;
		if (is_wall(Location(curTile.first - i, curTile.second)))
			++counter_up;
		if (is_wall(Location(curTile.first, curTile.second - i)))
			++counter_left;
		if (is_wall(Location(curTile.first, curTile.second + i)))
			++counter_right;
	}
	if(counter_down==step)
		moves.push_back(0);
	if (counter_up == step)
		moves.push_back(1);
	if (counter_left == step)
		moves.push_back(2);
	if (counter_right == step)
		moves.push_back(3);

	random_shuffle(moves.begin(), moves.end());
}

void Raster::createMaze(Location start, int& vertices, int& edges)
{
	int step, v_count=0, e_count=0;
	Location end = start;
	Location curTile = start;
	std::stack<Location> tileList;
	tileList.emplace(curTile);

	// start already put
	++v_count;

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	auto mt_rand = std::bind(std::uniform_int_distribution<int>(1, 3), std::mt19937(seed));

	while (v_count<vertices && e_count<edges && !tileList.empty())
	{
		/* randomize step length between 1,2,3 */
		step = mt_rand();
		if (v_count + step > vertices)
			step = vertices - v_count;

		vector<int> moves;
		findMoves(curTile, moves, step);

		if (!moves.empty())
		{
			Location on_path;
			int newEdges;
			int dir = moves[0];
			on_path.first = curTile.first;
			on_path.second = curTile.second;

			for (int i = 1; i <= step; ++i)
			{
				on_path.first += DIRS[dir].first;
				on_path.second += DIRS[dir].second;
				newEdges = countNewEdges(on_path);
				// don't do step next step if it creates too many new edges
				if ((e_count + newEdges) > edges)
					break;
				grid[on_path.first][on_path.second] = 1;
				// push newly created vertex to stack
				tileList.emplace(on_path);
				if(on_path >= end)
					end = on_path;
				v_count += 1;
				e_count += newEdges;
			}
		}

		curTile = tileList.top();
		tileList.pop();
	}

	this->end = end;

	// update vertices and edge count to values actually used
	vertices = v_count;
	edges = e_count;
}

int Raster::countNewEdges(Location loc)
{
	vector<Location> moves;
	int count=0;
	moves = neighbours(loc);
	return moves.size();

	//vertex does not lie on raster border
	if ( 1 <= loc.first && loc.first < height - 1 && 1 <= loc.second && loc.second < width - 1)
		count += (4 - moves.size());
	//vertex lies in raster corner
	else if (loc == std::make_pair(0, 0) || loc == std::make_pair(0, width - 1)
		|| loc == std::make_pair(height - 1, 0) || loc == std::make_pair(height - 1, width - 1))
		count += 1;
	//vertex lies on raster border
	else
		count += (3 - moves.size());
	return count;
}

bool Raster::readStartAndEnd()
{
	int x, y;
	std::cin >> x >> y;
	if (x >= 0 && x < height && y >= 0 && y < width && grid[x][y] == 1)
		start = std::make_pair(x, y);
	else
	{
		std::cout << "Wrong start point coordinates!" << std::endl;
		return false;
	}
	std::cin >> x >> y;
	if (x >= 0 && x < height && y >= 0 && y < width && grid[x][y] == 1)
		end = std::make_pair(x, y);
	else
	{
		std::cout << "Wrong end point coordinates!" << std::endl;
		return false;
	}
	return true;
}

vector<Raster::Location> Raster::neighbours(Location id) const
{
	int x, y, dx, dy;
	x = id.first;
	y = id.second;
	vector<Location> results;

	for (auto dir : DIRS)
	{
		dx = dir.first;
		dy = dir.second;
		Location next(x + dx, y + dy);
		if (is_valid(next))
			results.push_back(next);
	}
	return results;
}

bool Raster::readGrid()
{
	int x;
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
		{
			if (std::cin.good())
			{
				std::cin >> x;
				if (x != 1 && x != 0)
				{
					std::cout << "WARNING: wrong value in raster detected! "
						<< "Values must be 0 or 1." << std::endl;
					return false;
				}
				grid[i][j] = x;
			}
			else
			{
				std::cout << "ERROR: unxpected end of raster on input." << std::endl;
				return false;
			}
		}
	return true;
}

void Raster::generateGrid(int& vertices, int& edges)
{
	this->start = Location(0, 0);
	grid[0][0] = 1;
 	createMaze(this->start, vertices, edges);

	// print number of vertices and edges used to build the maze
	// (vertices and edges variables are modified inside createMaze)
	std::cout << "v: " << vertices << " e: " << edges << std::endl;
}

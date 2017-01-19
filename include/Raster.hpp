/**
 * Finding shortest path between points on square grid.
 *
 * @file Raster.hpp
 * @brief Declaration of class representing square grid.
 * @author Wiktor Franus
 */

#pragma once

#include <array>
#include <vector>
#include <stack>
#include <chrono>
#include <random>
#include <functional>
#include <algorithm>

using std::vector;
using std::array;
using std::pair;

class Raster
{
public:
	typedef pair<int, int> Location;
	static array<Location, 4> DIRS;

	Raster(int width_, int height_);
	Raster(const Raster& other);
	~Raster();

	//inlines
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	Location getStart() const { return start; }
	Location getEnd() const { return end; }
	int getVal(Location id) { return grid[id.first][id.second]; }

	/**
	 * Checks if given location has valid coordinates and is passable.
	 * @param id Location to check
	 * @return true if location is valid and passable
	 */
	bool is_valid(Location id) const;
	/**
	 * Checks if given location has valid coordinates and is a wall.
	 * @param id Location to check
	 * @return true if location is valid and is a wall (is not passable)
	 */
	bool is_wall(Location id) const;
	/**
	 * Reads from stdin and sets start and end point on grid.
	 * @return true if points was set or false if error occured
	 */
	bool readStartAndEnd();
	/**
	 * Reads and sets grid values form stdin
	 * @return true if points was set or false if error occured
	 */
	bool readGrid();
	/**
	 * Randomly selects start point and calls createMaze with given
	 * number of vertices and edges.
	 * @param vertices Number of vertices
	 * @param edges Number of edges
	 */
	void generateGrid(int& vertices, int& edges);

	vector<Location> neighbours(Location id) const;

private:
	/**
	 * Find possible moves for grid-generating algorithm.
	 * Move is ok if straight path from curTile of lenght
	 * field_width consists only of walls. Each direction
	 * is considered.
	 * @param curTile Location to find moves from
	 * @param moves Vector to put avaible moves into
	 */
	void findMoves(Location curTile, vector<int>& moves, int field_width);
	/**
	 * Create random maze using 0s and 1s. Algorithm stops when vertices
	 * or edges count is reached or when all grid has been filled.
	 * @param start_point Location to start from
	 * @param vertices Number of vertices (passable fields) to generate
	 * @param edges Number of edges (connections between vertices)
	 */
	void createMaze(Location start_point, int& vertices, int& edges);
	/**
	 * Returns number of new edges created by adding vertex at given
	 * location.
	 * @param loc Location of new vertex
	 * @return number of created edges
	 */
	int countNewEdges(Location loc);

	Location start = {0, 0};
	Location end = {0, 0};
	int width, height;

	/* 2D grid containg 0s and 1s */
	int **grid;
};

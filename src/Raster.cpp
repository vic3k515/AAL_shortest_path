#include "../include/Raster.hpp"

std::array<Raster::Location, 4> Raster::DIRS{ std::make_pair(1, 0), std::make_pair(0, -1),
											  std::make_pair(-1, 0), std::make_pair(0, 1) };

Raster::Raster(int width_, int height_) : width(width_), height(height_)
{
	grid = new int*[height_];
	for (int i = 0; i < height_; ++i)
		grid[i] = new int[width_]();
}

Raster::~Raster()
{
	for (int i = 0; i < height; ++i)
		delete[] grid[i];
	delete[] grid;
}

void Raster::neighbors2(Location curTile, vector<int>& moves, int step)
{
	int counter = 0;
	//down
	for(int i = 1; i <= step; ++i)
		if (is_wall(Location(curTile.first + i, curTile.second)))
			++counter;
	if(counter==step)
		moves.push_back(1);
	counter = 0;

	//up
	for (int i = 1; i <= step; ++i)
		if (is_wall(Location(curTile.first - i, curTile.second)))
			++counter;
	if (counter == step)
		moves.push_back(2);
	counter = 0;

	// left
	for (int i = 1; i <= step; ++i)
		if (is_wall(Location(curTile.first, curTile.second - i)))
			++counter;
	if (counter == step)
		moves.push_back(3);
	counter = 0;

	// right
	for (int i = 1; i <= step; ++i)
		if (is_wall(Location(curTile.first, curTile.second + i)))
			++counter;
	if (counter == step)
		moves.push_back(4);

	random_shuffle(moves.begin(), moves.end());
}

void Raster::createMaze(Location start, int& vertices, int& edges)
{
	bool exitPlaced = false;
	int step;
	Location curTile = start;
	std::stack<Location> tileList;
	tileList.emplace(curTile);

	int v = vertices, e = edges;
	// start already put
	--v;

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	//std::cout << "createMaze seed: " << seed << std::endl;
	// fixed seed: 30570839605938
	auto mt_rand = std::bind(std::uniform_int_distribution<int>(1, 3), std::mt19937(seed));

	while (v>0 && e>0 && !tileList.empty())
	{
		/* randomize step length between 2,4,6,8 */
		// constant step with value 2 results in labirynth
		step = mt_rand();
		//std::cout << step;
		if (v - step < 0)
			step = v;

		vector<int> moves;
		neighbors2(curTile, moves, step);

		if (!moves.empty())
		{
			Location temp, on_path;
			switch (moves[0])
			{
			case 1: // Down
/*				std::cout << "move down from " << curTile.first << "," << curTile.second <<
					" to " << curTile.first + step << "," << curTile.second << std::endl;*/
				temp.first = curTile.first + step;
				temp.second = curTile.second;

				for (int i = 1; i <= step; ++i)
				{
					on_path.first = curTile.first + i;
					on_path.second = curTile.second;
					int newEdges = countNewEdges(on_path);
					// don't do step if it creates too many new edges
					if ((e - newEdges) < 0)
					{
						temp.first = curTile.first + i - 1;
						break;
					}
					grid[curTile.first + i][curTile.second] = 1;
					tileList.emplace(on_path);
					v -= 1;
					e -= newEdges;
				}

				//if (curTile == temp) break;
				// even if no move was made, push curTile to stack -
				// when analyzed next time, move with
				// different length might be valid
				//curTile = temp;
				//tileList.push(curTile);

				break;

			case 2: // Up
/*				std::cout << "move up from " << curTile.first << "," << curTile.second <<
					" to " << curTile.first - step << "," << curTile.second << std::endl;*/
				temp.first = curTile.first - step;
				temp.second = curTile.second;

				for (int i = 1; i <= step; ++i)
				{
					on_path.first = curTile.first - i;
					on_path.second = curTile.second;
					int newEdges = countNewEdges(on_path);
					// don't do step if it creates too many new edges
					if ((e - newEdges) < 0)
					{
						temp.first = curTile.first - i + 1;
						break;
					}
					grid[curTile.first - i][curTile.second] = 1;
					tileList.emplace(on_path);
					v -= 1;
					e -= newEdges;
				}

				//curTile = temp;
				//tileList.push(curTile);

				break;

			case 3: // Left
/*				std::cout << "move left from " << curTile.first << "," << curTile.second <<
					" to " << curTile.first << "," << curTile.second-step << std::endl;*/
				temp.first = curTile.first;
				temp.second = curTile.second - step;

				for (int i = 1; i <= step; ++i)
				{
					on_path.first = curTile.first;
					on_path.second = curTile.second - i;
					int newEdges = countNewEdges(on_path);
					// don't do step if it creates too many new edges
					if ((e - newEdges) < 0)
					{
						std::cout << "LEFT" << std::endl;
						temp.second = curTile.second - i + 1;
						break;
					}
					grid[curTile.first][curTile.second - i] = 1;
					tileList.emplace(on_path);
					v -= 1;
					e -= newEdges;
				}

				//curTile = temp;
				//tileList.push(curTile);

				break;

			case 4: // Right
/*				std::cout << "move right from " << curTile.first << "," << curTile.second <<
					" to " << curTile.first << "," << curTile.second+step << std::endl;*/
				temp.first = curTile.first;
				temp.second = curTile.second + step;

				for (int i = 1; i <= step; ++i)
				{
					on_path.first = curTile.first;
					on_path.second = curTile.second + i;
					int newEdges = countNewEdges(on_path);
					// don't do step of lenght i if it creates too many new edges
					if ((e - newEdges) < 0)
					{
						std::cout << "RIGHT" << tileList.top().first << "," << tileList.top().second << std::endl;
						temp.second = curTile.second + i - 1;
						break;
					}
					grid[curTile.first][curTile.second + i] = 1;
					tileList.emplace(on_path);
					v -= 1;
					e -= newEdges;
				}

				//curTile = temp;
				//tileList.push(curTile);

				break;
			}//switch

			curTile = tileList.top();
			tileList.pop();
		}//if
		else
		{
			if (exitPlaced == false && v == vertices/2)
			{
				//std::cout << "placing exit " << std::endl;
				grid[curTile.first][curTile.second] = 1;
				exitPlaced = true;
				this->end = curTile;
			}
			curTile = tileList.top();
			tileList.pop();
		}
	}
	if (exitPlaced == false)
	{
		grid[curTile.first][curTile.second] = 1;
		this->end = curTile;
	}

	// update vertices and edge count to values actually used
	vertices -= v;
	edges -= e;
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
	if (x >= 0 && x < height & y >= 0 && y < width && grid[x][y] == 1)
		start = std::make_pair(x, y);
	else
	{
		std::cout << "Wrong start point coordinates!" << std::endl;
		return false;
	}
	std::cin >> x >> y;
	if (x >= 0 && x < height & y >= 0 && y < width && grid[x][y] == 1)
		end = std::make_pair(x, y);
	else
	{
		std::cout << "Wrong end point coordinates!" << std::endl;
		return false;
	}
	return true;
}
/* -------------*/
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
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	//std::cout << "generateGrid seed: " << seed << std::endl;
	// seed 30714654709773
	std::mt19937 mt_rand(seed);
	int rand_x = mt_rand() % height;
	int rand_y = mt_rand() % width;
	this->start = Location(rand_x, rand_y);
	grid[rand_x][rand_y] = 1;
	//std::cout << "GENERATOR start point: ("  << rand_x << "," << rand_y << ")" << std::endl;
 	createMaze(this->start, vertices, edges);
	// print number of vertices and edges used to build the maze:
	std::cout << "v: " << vertices << " e: " << edges << std::endl;
}

void Raster::draw()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (i == this->start.first && j == start.second)
				std::cout << "S";
			else if (i == this->end.first && j == end.second)
				std::cout << "E";
			else if (grid[i][j] == 0)
				std::cout << " ";
			else
				std::cout << "@" << "";
		}
		std::cout << std::endl;
	}
}

void Raster::clear()
{
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			grid[i][j] = 0;
}

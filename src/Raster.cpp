#include "../include/Raster.hpp"

Raster::Raster(int width_, int height_, bool from_cin) : width(width_), height(height_)
{
	grid = new int*[height_];
	for (int i = 0; i < height_; ++i)
		grid[i] = new int[width_]();

	if (from_cin)
	{
		for (int i = 0; i < height_; ++i)
			for (int j = 0; j < width_; ++j)
				std::cin >> grid[i][j];
	}
}

Raster::~Raster()
{
	for (int i = 0; i < height; ++i)
		delete[] grid[i];
	delete[] grid;
}

/* -------------- */
void Raster::neighbors2(Location curTile, vector<int>& moves, int magic_number)
{

	//if (((curTile.second - magic_number) >= 0) && grid[curTile.second - magic_number][curTile.first] == 0 )
	//down
	if(is_wall(Location(curTile.first + magic_number, curTile.second)))
	{
		moves.push_back(1);
	}
	//if (((curTile.second + magic_number) < height) && grid[curTile.second + magic_number][curTile.first] == 0 )
	//up
	if (is_wall(Location(curTile.first - magic_number, curTile.second)))
	{
		moves.push_back(2);
	}
	//if (((curTile.first - magic_number) >= 0) && grid[curTile.second][curTile.first - magic_number] == 0)
	// left
	if (is_wall(Location(curTile.first, curTile.second - magic_number)))
	{
		moves.push_back(3);
	}
	//if (((curTile.first + magic_number) < width) && grid[curTile.second][curTile.first + magic_number] == 0)
	// right
	if (is_wall(Location(curTile.first, curTile.second + magic_number)))
	{
		moves.push_back(4);
	}

	random_shuffle(moves.begin(), moves.end());
}


void Raster::createMaze2(int s_x, int s_y, int v, int e)
{
	bool exitPlaced = false;
	int field_width;
	Location curTile = Location(s_x, s_y);
	std::stack<Location> tileList;
	tileList.push(curTile);

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	auto mt_rand = std::bind(std::uniform_int_distribution<int>(2, width/2), std::mt19937(seed));

	// TODO: v and e should be checked first
	while (!tileList.empty() && v>0 && e>0)
	{
		/* randomize field_width value between 2,4,6,8 */
		field_width = 3;
		//while(!(field_width%4==0))
		//	field_width = mt_rand();

		vector<int> moves;
		neighbors2(curTile, moves, field_width);

		if (!moves.empty())
		{
			Location temp;
			switch (moves[0])
			{
			case 1: // Down
				temp.first = curTile.first + field_width;
				temp.second = curTile.second;

				for (int i = field_width; i > 0; --i)
				{
					grid[curTile.first + i][curTile.second] = 1;
				}
				//grid[curTile.second - 1][curTile.first] = 1;
				//grid[curTile.second - 2][curTile.first] = 1;
				curTile = temp;
				tileList.push(curTile);

				break;

			case 2: // Up
				temp.first = curTile.first - field_width;
				temp.second = curTile.second;

				for (int i = field_width; i > 0; --i)
				{
					grid[curTile.first - i][curTile.second] = 1;
				}
				//grid[curTile.second + 1][curTile.first] = 1;
				//grid[curTile.second + 2][curTile.first] = 1;
				curTile = temp;
				tileList.push(curTile);

				break;

			case 3: // Left
				temp.first = curTile.first;
				temp.second = curTile.second - field_width;

				for (int i = field_width; i > 0; --i)
				{
					grid[curTile.first][curTile.second - i] = 1;
				}

				//grid[curTile.second][curTile.first - 1] = 1;
				//grid[curTile.second][curTile.first - 2] = 1;
				curTile = temp;
				tileList.push(curTile);

				break;

			case 4: // Right 			
				temp.first = curTile.first;
				temp.second = curTile.second + field_width;

				for (int i = field_width; i > 0; --i)
				{
					grid[curTile.first][curTile.second + i] = 1;
				}

				//grid[curTile.second][curTile.first + 1] = 1;
				//grid[curTile.second][curTile.first + 2] = 1;
				curTile = temp;
				tileList.push(curTile);

				break;
			}
		}
		else
		{
			if (exitPlaced == false)
			{
				grid[curTile.first][curTile.second] = 1;
				exitPlaced = true;
				this->end = curTile;
			}
			curTile = tileList.top();
			tileList.pop();
		}
	}



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
/*
void Raster::createMaze(int start_x, int start_y, int v, int e)
{
	std::stack<Location> s;
	Location curr = Location(start_x, start_y);
	s.push(curr);
	bool exitPlaced = false;

	while (!s.empty() && v > 0 && e > 0)
	{

		vector<Location> moves = neighbours(curr);
		std::random_shuffle(moves.begin(), moves.end());

		if (!moves.empty())
		{
			Location next = moves[0];
			grid[next.first][next.second] = 1;
			curr = next;
			s.push(curr);
		}
		else
		{
			if (exitPlaced == false)
			{
				exitPlaced = true;
				this->end = curr;
			}
			curr = s.top();
			s.pop();
		}

	}
}
*/
void Raster::generateGrid(int vertices, int edges)
{
	//srand(time(NULL));
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 mt_rand(seed);
	int rand_x = mt_rand() % height;
	int rand_y = mt_rand() % width;
	this->start = Location(rand_x, rand_y);
	grid[rand_x][rand_y] = 1;
	std::cout << "GENERATOR start point: ("  << rand_x << "," << rand_y << ")" << std::endl;
	//createMaze(rand_x, rand_y, vertices, edges);
 	createMaze2(rand_x, rand_y, vertices, edges);
}

void Raster::draw()
{
	//// print top ruler
	//std::cout << "  ";
	//for (int row = 0; row < width; ++row)
	//	std::cout << "A";

	std::cout << std::endl;
	for (int i = 0; i < height; ++i)
	{
		// print left ruler
		//std::cout << "." << " ";
		for (int j = 0; j < width; ++j)
		{
			if (i == this->start.first && j == start.second)
				//std::cout << grid[i][j] << "";
				std::cout << "S";
			else if (i == this->end.first && j == end.second)
				//std::cout << grid[i][j] << "";
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

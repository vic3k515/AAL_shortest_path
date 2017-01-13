#pragma once
#include "../lib/CImg.h"
#include "../include/Raster.hpp"
#include <vector>

using namespace cimg_library;

/* Draws black and white image with size width x height of raster pointed by rptr 
   and shortest path between raster's start and end points given in path parameter.
   Each point of raster will have size of pixel_size. */
void drawResult(int width, int height, Raster* rptr, std::vector<std::pair<int,int>>& path, int pixel_size = 10)
{
	// Create display object and initialize its pixels with 0s = black color
	CImgDisplay
		draw_disp(pixel_size* width, height * pixel_size, "Shortest Path", 0);

	const unsigned char
		red[] = { 255,0,0 },
		green[] = { 0,255,0 },
		blue[] = { 0,0,255 },
		black[] = { 0,0,0 },
		white[] = { 255,255,255 };


	// Handle display window resizing (if any)
	//draw_disp.resize();

	// Create and display the image of raster and path
	CImg<unsigned char> img(draw_disp.width(), draw_disp.height(), 1, 3, 0);

	for (int i = rptr->getHeight() - 1; i >= 0; --i)
		for (int j = rptr->getWidth(); j >= 0; --j)
		{
			std::pair<int, int> tmp = std::make_pair(i, j);
			int y = i*pixel_size, x = j*pixel_size;

			if (tmp == rptr->getStart())
				img.draw_rectangle(x, y, x + pixel_size, y + pixel_size, red, 1);
			else if (tmp == rptr->getEnd())
				img.draw_rectangle(x, y, x + pixel_size, y + pixel_size, green, 1);
			else if (rptr->getVal(tmp) == 1)
				img.draw_rectangle(x, y, x + pixel_size, y + pixel_size, white, 1);
		}

	// Start drawing path from 2nd item, because end is already drown
	if(path.size()>1)
		for (auto it = path.begin() + 1; it != path.end(); ++it)
		{
			int y = ((*it).first)*pixel_size, x = ((*it).second)*pixel_size;
			img.draw_rectangle(x, y, x + pixel_size, y + pixel_size, blue, 1);
		}

	img.display(draw_disp);
	while (!draw_disp.is_closed() && !draw_disp.is_keyESC() && !draw_disp.is_keyQ())
	{
		// wait for windows close or ESC press or Q press
	}
}
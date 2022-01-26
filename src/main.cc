#include "color.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

int main() {
	// File
	std::ofstream helloFile;
	char path[] = "..\\data\\image.ppm";
	
	// TODO: Fool proof file io
	helloFile.open(path);

	// Image
	
	const int image_width = 256;
	const int image_height = 256;

	// Render
	
	helloFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(double(i)/(image_width-1), double(j)/(image_height-1), 0.25);
//			color pixel_color(0,0,0);
			write_color(helloFile, pixel_color);
		}
	}

	helloFile.close();

	std::cerr << "\nDone.\n";
	return(0);
}

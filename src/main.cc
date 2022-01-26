#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>
#include <fstream>

//! A function that takes in two arguments, returns a color object.
/*! 
  \param r ray&, casted ray for drawing the scene.
  \param world hittable&, hittable object representing objects in the world.
  \return The color of the pixel to be drawn in the scene.
 */
color ray_color(const ray& r, const hittable& world)
{
	hit_record rec;
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + color(1,1,1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
	// File
	std::ofstream helloFile;
	char path[] = "..\\data\\image.ppm";
	
	// TODO: Fool proof file io
	helloFile.open(path);

	// Image
	
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 960;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;

	// World
	
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
	world.add(std::make_shared<sphere>(point3(0,-100.4,-1), 100));

	// Camera
	
	camera cam;
	
	// Render
	
	helloFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto u = (i + random_double()) / (image_width-1);
				auto v = (j + random_double()) / (image_height-1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
//			color pixel_color(double(i)/(image_width-1), double(j)/(image_height-1), 0.25);	// color gradient
//			color pixel_color(0,0,0);							// black
			write_color(helloFile, pixel_color, samples_per_pixel);
		}
	}

	helloFile.close();

	std::cerr << "\nDone.\n";
	return(0);
}

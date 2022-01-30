#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <iostream>
#include <fstream>

//! A function that takes in two arguments, returns a color object.
/*! 
  \param r ray&, casted ray for drawing the scene.
  \param world hittable&, hittable object representing objects in the world.
  \return The color of the pixel to be drawn in the scene.
 */
color ray_color(const ray& r, const hittable& world, int depth)
{
	hit_record rec;
	
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
	{
		return color(0,0,0);
	}

	if (world.hit(r, 0.001, infinity, rec))
	{
		// TODO: allow of toggling of different diffuse methods?
//		point3 target = rec.p + rec.nomral + random_in_unit_sphere();	// Aproximation of Lambertian diffuse
//		point3 target = rec.p + rec.normal + random_unit_vector();	// Lambertian diffuse
//		point3 target = rec.p + random_in_hemisphere(rec.normal);	// Hemispherical scattering
//		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth-1);
		}
		return color(0,0,0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
//	return (1.0-t)*color(0.5, 0.7, 1.0) + t*color(0, 0, 0);
}

int main() {
	// File
	std::ofstream helloFile;
	char path[] = "..\\data\\image.ppm";
	
	// TODO: Fool proof file io
	helloFile.open(path);

	// Image
	
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 1280; // nHD: 640, qHD: 960, HD: 1280, Full HD: 1920, QHD: 2560, 4K UHD: 3840
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World
	
//	auto R = cos(pi/4);
	hittable_list world;

	auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
//	auto material_center = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
//	auto material_left   = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
	auto material_center = std::make_shared<dielectric>(1.5);
	auto material_water = std::make_shared<dielectric>(1.333);
	auto material_left   = std::make_shared<dielectric>(1.7);
	auto material_right  = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);
	
	world.add(std::make_shared<sphere>(point3( 0.5,   0.0, -2),   0.5,     material_right));
	world.add(std::make_shared<sphere>(point3( 0.0, -0.25, -1),  0.25,     material_center));
	world.add(std::make_shared<sphere>(point3( 0.0, -0.25, -1), -0.15,     material_water));
	world.add(std::make_shared<sphere>(point3(-0.5,   0.0, -2),   0.5,     material_left));
	world.add(std::make_shared<sphere>(point3(-0.5,   0.0, -2),  -0.3,     material_left));
	world.add(std::make_shared<sphere>(point3( 0.0,-100.5, -2), 100.0,     material_ground));
//	world.add(std::make_shared<sphere>(point3( 0.0,-3179.5,-2), 3178.5, material_ground));
//	world.add(std::make_shared<sphere>(point3( 0.0, 0.0,      1), 0.5,    material_center));

	// Camera
	
	camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 20, aspect_ratio);
	
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
				pixel_color += ray_color(r, world, max_depth);
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

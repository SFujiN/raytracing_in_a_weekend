#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "triangle.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>

enum RES { nHD = 640, qHD = 960, HD = 1280, FHD = 1920, QHD = 2560, UHD = 3840};

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

hittable_list cover_scene()
{
	hittable_list world;

	auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(std::make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = random_double();
			point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

			if ((center - point3(3, 0.2, 0)).length() > 0.9)
			{
				std::shared_ptr<material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = random_vec3() * random_vec3();
					sphere_material = std::make_shared<lambertian>(albedo);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = random_vec3(0.5, 1); 
					auto fuzz = random_double(0, 0.5);
					sphere_material = std::make_shared<metal>(albedo, fuzz);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = std::make_shared<dielectric>(1.5);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<dielectric>(1.5);
	world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}

hittable_list my_scene()
{
	hittable_list world;

 	auto material_ground = std::make_shared<lambertian>(color(0.11, 0.21, 0.18));
	auto material_center = std::make_shared<dielectric>(1.5);
	auto material_water = std::make_shared<dielectric>(1.333);
	auto material_left   = std::make_shared<dielectric>(1.7);
	auto material_right  = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);
	
	world.add(std::make_shared<sphere>(point3( 0.5,   0.0, -1),   0.5,     material_right));
	world.add(std::make_shared<sphere>(point3( 0.0, -0.25, -0),  0.25,     material_center));
	world.add(std::make_shared<sphere>(point3( 0.0, -0.25, -0), -0.15,     material_water));
	world.add(std::make_shared<sphere>(point3(-0.5,   0.0, -1),   0.5,     material_left));
	world.add(std::make_shared<sphere>(point3(-0.5,   0.0, -1),  -0.3,     material_left));
	world.add(std::make_shared<sphere>(point3( 0.0,-100.5, -1), 100.0,     material_ground));

	return world;
}

void render(std::ostream& out, const camera& cam, const hittable_list& world, int image_width, int image_height, int max_height, int min_height, int samples_per_pixel, int max_depth)
{
	for (int j = max_height-1; j >= min_height; --j)
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
			write_color(out, pixel_color, samples_per_pixel);
		}
	}
}

int main() {
	// File
	std::ofstream helloFile;
	char path[] = "../data/image.ppm";

	// Threads
	size_t num_threads = std::thread::hardware_concurrency();
	std::vector<std::thread> pool;
	std::vector<std::stringstream> s_pool(num_threads);
	
	// TODO: Fool proof file io
	helloFile.open(path);

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = nHD; // nHD: 640, qHD: 960, HD: 1280, Full HD: 1920, QHD: 2560, 4K UHD: 3840
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 500;
	const int max_depth = 50;

	// World
	auto world = cover_scene();
//	auto world = my_scene();
	
	auto material_ground = std::make_shared<lambertian>(color(1,0,0));
	world.add(std::make_shared<triangle>(vec3(0,-0.25,0),vec3(1,-0.25,0),vec3(1,0.75,0),material_ground));

	// Camera
	point3 lookfrom(13,2,3);
	point3 lookat(0,0,0);
	vec3 vup(0,1,0);
	auto dist_to_focus = 13.5;
	auto aperture = 0.1;

	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
	
	// Render
	helloFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	for (size_t i = 0; i < num_threads; i++)
	{
		int max_h = image_height * (num_threads - i) / num_threads;
		int min_h = image_height * (num_threads - (i + 1)) / num_threads;
		pool.push_back(std::thread(&render, std::ref(s_pool[i]), std::ref(cam), std::ref(world), image_width, image_height, max_h, min_h, samples_per_pixel, max_depth));
	}

	for (auto& th : pool)
	{
		th.join();
	}

	for (auto& ss : s_pool)
	{
		helloFile << ss.str();
	}

//	render(ss, cam, world, image_width, image_height, samples_per_pixel, max_depth);

	helloFile.close();

	std::cerr << "\nDone.\n";
	return(0);
}

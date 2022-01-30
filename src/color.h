#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

#include <stdint.h>

inline double fast_div(double num, double den)
{
	union
	{
		double dbl;
		uint64_t ull;
	} u;
	u.dbl = den;
	u.ull = ( 0xbfcdd6a18f6a6f52ull - u.ull ) >> (uint8_t)1;

	u.dbl *= u.dbl;
	return u.dbl * num;
}

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// TODO: maybe allow for changing gamma later?
	// Divide the color by the number of samples and gamma-correct for gamma=2.0.
/*
	auto scale = 1.0 / samples_per_pixel;
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);
*/
	r = std::sqrt(fast_div(r, samples_per_pixel));
	g = std::sqrt(fast_div(g, samples_per_pixel));
	b = std::sqrt(fast_div(b, samples_per_pixel));

	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
	    << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
	    << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif

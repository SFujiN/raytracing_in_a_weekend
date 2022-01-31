#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

typedef struct triangle : hittable
{
	vec3 v[3];
	std::shared_ptr<material> mat_ptr;

	triangle() {}
	triangle(vec3 v0, vec3 v1, vec3 v2, std::shared_ptr<material> m) : v{v0, v1, v2}, mat_ptr(m) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
} triangle;

// Moller-Trumbore ray-triangle intersection algorithm
bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	const double EPSILON = 0.0000001;
	vec3 v0 = v[0];
	vec3 v1 = v[1];
	vec3 v2 = v[2];
	vec3 edge1, edge2, h, s, q;
	double a, f, u, v;
	edge1 = v1 - v0;
	edge2 = v2 - v1;
	h = cross(r.direction(), edge2);
	a = dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
	{
		return false;	// ray parallel to triangle
	}
	f = 1.0/a;
	s = r.origin() - v0;
	u = f * dot(s, h);
	if (u < 0.0 || u > 1.0)
	{
		return false;
	}
	q = cross(s, edge1);
	v = f * dot(r.direction(), q);
	if (v < 0.0 || u + v > 1.0)
	{
		return false;
	}
	double t = f * dot(edge2, q);
	if (t > EPSILON) // ray intersection
	{
		rec.t = t;
		rec.p = r.origin() + r.direction() * t;
		rec.mat_ptr = mat_ptr;
		return true;
	}
	return false;
}


#endif

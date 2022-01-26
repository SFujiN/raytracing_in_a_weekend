#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

//!	vec3 struct.
/*!
	A struct to represent 3D vectors.
*/
typedef struct vec3
{
	//!	An array of doubles.
	/*!	An array of doubles to store the x, y, and z coordinates of a vec3. */
	double e[3];

	//!	vec3 constructor.
	/*!	default constructor for vec3. */
	vec3() : e{0,0,0} {}
	//!	vec3 constructor.
	/*!
		\param e0 double representing x position.
		\param e1 double representing y position.
		\param e2 double representing z position.
	*/
	vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

	//!	function to return the x position
	/*!
	 	\return e[0] which represents the x position.
	*/
	double x() const 
	{
		return e[0];
	}
	//!	function to return the y position
	/*!
	 	\return e[1] which represents the y position.
	*/
	double y() const
	{
		return e[1];
	}
	//!	function to return the z position
	/*!
	 	\return e[2] which represents the z position.
	*/
	double z() const
	{
		return e[2];
	}

	//!	overloaded unary negation operator for vec3.
	/*!
		\return vec3 negation of current vec3
	*/
	vec3 operator-() const
	{
		return vec3(-e[0], -e[1], -e[2]);
	}
	//!	overloaded subscript operator for vec3.
	/*!
	 	\param i int for index of element in e.
	 	\return the element of e in index i.
	*/
	double operator[](int i) const
	{
		return e[i];
	}
	//!	overloaded subscript operator for vec3.
	/*!
	 	\param i int for index of element in e.
		\return the address of element e in index i.
	*/
	double& operator[](int i)
	{
		return e[i];
	}

	//!	overloaded increment assignment operator for vec3.
	/*!
	 	\param v the vector being added then assigned to current vector.
		\return pointer to current vector.
	*/ 
	vec3& operator+=(const vec3 &v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	//!	overloaded multiplication assignment operator for vec3.
	/*!
	 	\param t double to scale elements of e to.
		\return pointer to current vector.
	*/ 
	vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
		
	}

	//!	overloaded divide assignment operator for vec3.
	/*!
	 	\param t double to divide the elements of e by.
		\return pointer to current vector.
	*/
	vec3& operator/=(const double t)
	{
		return *this *= 1/t;
	}

	//!	length function to return the length of current vec3.
	/*!
	 	\param t double representing the length of the current vector.
	*/
	double length() const
	{
		return std::sqrt(length_squared());
	}

	//!	length_squared function to find the square of each element in e added together.
	/*!
	 	\return the sum of the elements of e squared.
	*/
	double length_squared() const
	{
		return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
	}

} point3, color;

// vec3 Utility Functions

//!	overloaded operator for << output streams, basically outputing a vec3 in 'x y z' format.
/*!
	\param out the output stream.
	\param v the vec3 that is to be outputed.
	\return the stream with the vec3 outputed in 'x y z' format.
*/
inline std::ostream& operator<<(std::ostream &out, const vec3 &v)
{
	return out << v.e[0] << ' ' << v.e[1]<< ' ' << v.e[2];
}

//!	overloaded + addition operator for adding two vectors together.
/*!
	\param u the left hand side vec3.
	\param v the right hand side vec3.
	\return a vec3 that represents the addition of vectors u + v.
*/
inline vec3 operator+(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

//!	overloaded - subtraction operator for subtracting two vectors together.
/*!
 	\param u the left hand side vec3.
	\param v the right hand side vec3.
	\return a vec3 representing the subtraction of u - v.
*/
inline vec3 operator-(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

//!	overloaded * multiplication operator for multiplying two vectors together. I honestly have no idea why you'd do it this way.
/*!
 	\param u the left hand side vec3.
	\param v the right hand side vec3.
	\return a vec3 where its x = u.e[0] * v.e[0], y = u.e[1] * v.e[1], and z = u.e[2] * v.e[2].
*/
inline vec3 operator*(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

//!	overloaded * multiplication operator for multipying a scalar and a vector together.
/*!
	\param t double to represent the left hand scalar.
	\param v vec3 to represent the right hand vector.
	\return a vec3 scaled by up a factor of t.
*/
inline vec3 operator*(double t, const vec3 &v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

//!	overloaded * multiplication operator for multiplying a vector with a scalar in that order.
/*!
	\param v vec3 to represent the left hand vector.
	\param t double to represent the right hand scalar.
	\return a vec3 scaled up by a factor of t.
*/
inline vec3 operator*(const vec3 &v, double t)
{
	return t * v;
}

//!	overloaded / division operator for dividing a vector by a scalar.
/*!
	\param v vec3 to represent the left hand vectors.
	\param t double to represent the right hand scalar.
	\return a vec3 that has been scaled down by a factor of t.
*/
inline vec3 operator/(const vec3 &v, double t)
{
	return (1/t) * v;
}

//!	function to calculate the dot product of two vectors, resulting in a scalar.
/*!
	\param u vec3 to represent the left hand vector.
	\param v vec3 to represent the right hand vector.
	\return a double representing the dot product of u * v.
*/
inline double dot(const vec3 &u, const vec3 &v)
{
	return u.e[0] * v.e[0]
	     + u.e[1] * v.e[1]
	     + u.e[2] * v.e[2];
}

//!	function to calculate the cross product of two vectors, resulting in a vector.
/*!
	\param u vec3 to represent the left hand vector.
	\param v vec3 to represent the right hand vector.
	\return a vec3 representing the cross product of u x v.
*/
inline vec3 cross(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		    u.e[2] * v.e[0] - u.e[0] * v.e[2],
		    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

//!	function to calculate the unit vector pointing the direction of v.
/*!
 * 	\param v vec3 vector to be used for calculating the unit vector.
 * 	\return vec3 representing the unit vector.
*/
inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

//!	function to return a random vector.
/*
	\return a random vec3
*/
inline static vec3 random()
{
	return vec3(random_double(), random_double(), random_double());
}

//!	function to return a random vector with values in range min to max.
/*
	\param min double for the minimum value.
	\param max double fro the maximum value.
	\return a random vec3.
*/
inline static vec3 random(double min, double max)
{
	return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

//!	function to generate and return a random vector with length >= 1.
/*
	\return a vec3 random vec3.
*/
vec3 random_in_unit_sphere()
{
	for (;;)
	{
		auto p = random(-1,1);
		if (p.length_squared() >= 1)
		{
			continue;
		}
		return p;
	}
}

#endif

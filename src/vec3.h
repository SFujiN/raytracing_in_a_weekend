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
	 	\param double representing the length of the current vector.
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

// TODO: the rest of the documentation
// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v)
{
	return out << v.e[0] << ' ' << v.e[1]<< ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t)
{
	return t * v;
}

inline vec3 operator/(const vec3 &v, double t)
{
	return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v)
{
	return u.e[0] * v.e[0]
	     + u.e[1] * v.e[1]
	     + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		    u.e[2] * v.e[0] - u.e[0] * v.e[2],
		    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

#endif

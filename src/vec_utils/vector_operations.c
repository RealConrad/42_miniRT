
#include "mini_rt.h"

/**
 * @brief Substracts vector 2 from vector 1
 * @param v1 the minuend
 * @param v2 the subtrahend
 * @return the difference of the two vectors
 * @throw if the difference is bigger than
 * DOUBLE_MAX or smaller DOUBLE_MIN, it will overflow
 */
t_vector	vec_subtract(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

/**
 * @brief Adds two vectors together
 * @param v1 addend 1
 * @param v2 addend 2
 * @return the sum of the vectors
 * @throw if the sum of two of the vector values is bigger
 * than DOUBLE_MAX or smaller DOUBLE_MIN, it will overflow
 */
t_vector	vec_add(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

/**
 * @brief Divides vector 1 by vector 2
 * @param v1 the dividend
 * @param v2 the divisor
 * @return the quotient of v1 and v2
 * @throws if the quotient is bigger than DOUBLE_MAX or
 * smaller DOUBLE_MIN, it will overflow
 */
t_vector	vec_divide(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z});
}

/**
 * @brief Multiplies two vectors
 * @param v1 factor 1
 * @param v2 factor 2
 * @return the product of factor 1 and 2
 * @throw if the product is bigger than DOUBLE_MAX
 * or smaller than DOUBLE_MIN, it will overflow
 */
t_vector	vec_multiply(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

/**
 * @brief Scales vector to length of 1 (normalizes a vector)
 * @param v the vector to normalise
 * @return the normalised vector
 * @note if issues arrise, try checking lenght < 0 instead of < 1e-10
 */
t_vector	normalize_vector(t_vector v)
{
	double		length;
	t_vector	unit;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length < 1e-10)
		return ((t_vector){0, 0, 0});
	unit.x = v.x / length;
	unit.y = v.y / length;
	unit.z = v.z / length;
	return (unit);
}

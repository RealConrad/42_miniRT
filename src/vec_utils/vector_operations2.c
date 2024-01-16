
#include "mini_rt.h"

/**
 * @brief Takes 2 vectors and returns a single scalar value. This works
 * by multiplying the 2 vectors elements.
 * @param v1 
 * @param v2 
 * @return the dot product
 * @throw if the dot product is bigger DOUBLE_MAX or smaller
 * DOUBLE min, it will overflow
 */
double	dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/**
 * @brief Converts the given number to a vector.
 *
 * The X,Y,Z elements of the vector will all be set to `n`.
 * @param n The number to be converted to a vector.
 * @return A newly created vector from `n`.
 */
t_vector	to_vec(double n)
{
	return ((t_vector){n, n, n});
}

/**
 * @brief Multiplies the vector by factor scalar
 * @param v the vector as product 1
 * @param scalar the scalar as product 2
 * @return the product of the vector and the scalar
 * @throw if the product is bigger DOUBLE_MAX or smaller
 * DOUBLE min, it will overflow
 */
t_vector	vec_scalar_multiply(t_vector v, double scalar)
{
	return ((t_vector){v.x * scalar, v.y * scalar, v.z * scalar});
}

/**
 * @brief Gets the lenght of a vector
 * @param v the vector
 * @return the lenght of the vector
 * @throw if the vector squared is bigger DOUBLE_MAX or smaller
 * DOUBLE min, it will overflow
 */
double	vec_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

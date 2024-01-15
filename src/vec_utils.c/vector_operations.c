#include "mini_rt.h"

t_vector	vec_subtract(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vector	vec_add(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vector	vec_divide(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z});
}

t_vector	vec_multiply(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

/**
 * @brief Scales vector to length of 1 (normalizes a vector)
 * @param v 
 * @return 
 */
t_vector	normalize_vector(t_vector v)
{
	double		length;
	t_vector	unit;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	unit.x = v.x / length;
	unit.y = v.y / length;
	unit.z = v.z / length;
	return (unit);
}

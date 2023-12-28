#include "mini_rt.h"

t_vector	vec_subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result = (t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	return (result);
}

t_vector	vec_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result = (t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	return (result);
}

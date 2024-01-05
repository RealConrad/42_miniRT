#include "mini_rt.h"


/**
 * @brief 
 * @param  
 * @param t The point of intersection of an object at a distance from its origin
 * @return 
 */
t_vector	ray_at(t_ray ray, double t)
{
	t_vector	result;

	result = vec_add(ray.origin, vec_multiply(ray.direction, to_vec(t)));
	return (result);
}

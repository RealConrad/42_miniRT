
#include "mini_rt.h"


/**
 * @brief returns the point of the ray at distance t
 * @param ray
 * @param t The point of intersection of an object at a distance from its origin
 * @return the point from ray origin at distance t
 */
t_vector	ray_at(t_ray ray, double t)
{
	t_vector	result;

	result = vec_add(ray.origin, vec_multiply(ray.direction, to_vec(t)));
	return (result);
}

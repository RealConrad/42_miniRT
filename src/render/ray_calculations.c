
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

	result = vec_add(ray.origin, vec_scalar_multiply(normalize_vector(ray.direction), t));
	return (result);
}

/**
 * @brief Gets the ray information
 * @param ray 
 * @param objects 
 * @return true if the ray hits anything, otherwise false
 */
bool	get_ray_intersection(t_ray *ray, t_object *objects)
{
	t_object	*temp;
	double		distance;
	t_object	*closest;
	double		old_hit;

	closest = NULL;
	temp = objects;
	old_hit = 0;
	while (temp)
	{
		distance = hit_object(temp, ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
		{
			closest = temp;
			old_hit = distance;
		}
		temp = temp->next;
	}
	if (closest == NULL)
		return (false);
	hit_object(closest, ray);
	return (true);
}

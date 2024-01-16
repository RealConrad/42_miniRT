
#include "mini_rt.h"

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

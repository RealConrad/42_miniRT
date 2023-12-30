#include "mini_rt.h"

static t_colour	blend_colour(t_colour c1, t_colour c2, double t);
static t_colour	get_object_colour(t_object *object);

t_colour	get_ray_colour(t_ray ray, t_object *objects)
{
	t_vector	normalized_ray_direction;
	double		ratio;
	t_object	*temp;

	temp = objects;
	(void)get_object_colour;
	while (temp)
	{
		if (check_object_intersection(temp, ray))
			return (get_object_colour(temp));
		temp = temp->next;
	}
	normalized_ray_direction = normalize_vector(ray.direction);
	ratio = 0.5  * (normalized_ray_direction.y + 1.0);
	return (blend_colour((t_colour){128, 178, 255}, (t_colour){255, 255, 255}, ratio));
}

/**
 * @brief Blends colour based on given ratio
 * @param c1 
 * @param c2 
 * @param t 
 * @return 
 */
static t_colour	blend_colour(t_colour c1, t_colour c2, double ratio)
{
	t_colour	result;

	result.r = (int)((1 - ratio) * c1.r + ratio * c2.r);
	result.g = (int)((1 - ratio) * c1.g + ratio * c2.g);
	result.b = (int)((1 - ratio) * c1.b + ratio * c2.b);
	return (result);
}

/**
 * @brief Gets the colour property of the given object
 * @param object 
 * @return 
 */
t_colour	get_object_colour(t_object *object)
{
	if (object->cylinder)
		return (object->cylinder->colour);
	else if (object->plane)
		return (object->plane->colour);
	else if (object->sphere)
		return (object->sphere->colour);
	return ((t_colour){255, 255, 255});
}

#include "mini_rt.h"

static t_colour	blend_colour(t_colour c1, t_colour c2, double t);
static t_colour	get_object_colour(t_ray ray, t_object *objects);

t_colour	get_ray_colour(t_ray ray, t_object *objects)
{
	t_vector	normalized_ray_direction;
	double		ratio;
	t_colour	ray_colour;

	ray_colour = get_object_colour(ray, objects);
	if (legal_colour(ray_colour))
	{
		return (ray_colour);
	}
	normalized_ray_direction = normalize_vector(ray.direction);
	ratio = 0.5  * (-normalized_ray_direction.y + 1.0);
	ray_colour = blend_colour((t_colour){128, 178, 255}, (t_colour){255, 255, 255}, ratio);
	return (ray_colour);
}

static t_colour	get_object_colour(t_ray ray, t_object *objects)
{
	t_object	*temp;
	t_vector	hit_point;
	t_vector	n;
	double		t;
	t_colour	colour;

	colour = (t_colour){-1, -1, -1};
	temp = objects;
	while (temp)
	{
		t = hit_object(temp, ray);
		if (t > 0.0 && temp->sphere != NULL)
		{
			hit_point = ray_at(ray, t);
			n = normalize_vector(vec_subtract(hit_point, temp->sphere->cords));
			return ((t_colour){0.5 * (n.x + 1) * 255, 0.5 * (n.y + 1) * 255, 0.5 * (n.z + 1) * 255});
		}
		else if (t > 0.0 && temp->plane != NULL)
		{
			// hit_point = ray_at(ray, t);
			// n = normalize_vector(vec_subtract(hit_point, temp->plane->cords));
			return (temp->plane->colour);
		}
		temp = temp->next;
	}
	return (colour);
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

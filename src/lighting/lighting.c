
#include "mini_rt.h"

t_colour	lighting(t_colour ray_col, t_scene *scene, t_ray ray)
{
	t_vector	hit_point;

	if (get_hit_point(ray, scene->objects, &hit_point) == false)
		return (get_ambient_light(ray_col, scene->amb_light));
}

static bool	get_hit_point(t_ray ray, t_object *objects, t_vector *hit_point)
{
	t_object	*temp;
	double		old_hit;
	double		distance;

	temp = objects;
	old_hit = 0;
	{
		distance = hit_object(temp, ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
			old_hit = distance;
		temp = temp->next;
	}
	if (old_hit == 0)
		return (false);
	*hit_point = ray_at(ray, old_hit);
	return (true);
}


#include "mini_rt.h"

static bool		get_hit_point(t_ray ray, t_object *objects, t_vector *hit_point);
static t_ray	get_light_ray(t_light light, t_vector hit_point);
static bool		light_hit(t_ray ray, t_object *objects, t_vector hit_point);

t_colour	lighting(t_colour ray_col, t_scene *scene, t_ray ray)
{
	t_vector	hit_point;
	t_ray		light_ray;

	if (get_hit_point(ray, scene->objects, &hit_point) == false)
		return (get_ambient_light(ray_col, scene->amb_light));
	light_ray = get_light_ray(scene->light, hit_point);
	if (light_hit(light_ray, scene->objects, hit_point) == true)
		return ((t_colour){255, 255, 0});
		// return (ray_col);
	return ((t_colour){0, 0, 0});
}

static t_ray	get_light_ray(t_light light, t_vector hit_point)
{
	t_ray	light_ray;

	light_ray.origin = hit_point;
	light_ray.direction = vec_subtract(light.cords, hit_point);
	light_ray.direction = normalize_vector(light_ray.direction);
	return (light_ray);
}

static bool	get_hit_point(t_ray ray, t_object *objects, t_vector *hit_point)
{
	t_object	*temp;
	double		old_hit;
	double		distance;

	temp = objects;
	old_hit = 0;
	while (temp != NULL)
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

static bool	light_hit(t_ray ray, t_object *objects, t_vector hit_point)
{
	t_object	*temp;
	double		old_hit;
	double		distance;

	temp = objects;
	old_hit = 0;
	while (temp != NULL)
	{
		distance = hit_object(temp, ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
			old_hit = distance;
		temp = temp->next;
	}
	if (old_hit == 0)
		return (true);
	return (false);
}

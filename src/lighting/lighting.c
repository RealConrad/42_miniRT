
#include "mini_rt.h"

static t_ray	get_light_ray(t_light light, t_vector hit_point);
static bool		light_hit(t_ray ray, t_object *objects, t_vector hit_point);

void	lighting(t_scene *scene, t_ray *ray)
{
	t_ray		light_ray;

	if (ray->distance < 0.0)
	{
		ray->ray_colour = get_ambient_light((t_colour){255, 255, 255}, scene->amb_light);
		return ;
	}
	light_ray = get_light_ray(scene->light, ray->hit_point);
	if (light_hit(light_ray, scene->objects, ray->hit_point) == true)
	{
		ray->ray_colour = (t_colour){255, 255, 0};
		return ;
	}
	ray->ray_colour = (t_colour){0, 0, 0};
}

static t_ray	get_light_ray(t_light light, t_vector hit_point)
{
	t_ray	light_ray;

	light_ray.origin = hit_point;
	light_ray.direction = vec_subtract(light.cords, hit_point);
	light_ray.direction = normalize_vector(light_ray.direction);
	// if (hit_point.y > light.cords.y)
	// 	light_ray.direction.y *= -1;
	return (light_ray);
}

static bool	light_hit(t_ray ray, t_object *objects, t_vector hit_point)
{
	t_object	*temp;
	double		old_hit;
	double		distance;

	temp = objects;
	old_hit = 0;
	(void)hit_point;
	while (temp != NULL)
	{
		distance = hit_object(temp, &ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
			old_hit = distance;
		temp = temp->next;
	}
	if (old_hit == 0)
		return (true);
	return (false);
}

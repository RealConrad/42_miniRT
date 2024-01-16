
#include "mini_rt.h"

double	hit_object(t_object *object, t_ray *ray)
{
	if (object->sphere != NULL)
		return (hit_sphere(object->sphere, ray), ray->distance);
	else if (object->cylinder != NULL)
	{
		hit_cylinder(object->cylinder, ray);
		ray->ray_colour = object->cylinder->colour;
		ray->hit_point = ray_at(*ray, ray->distance);
		return (ray->distance);
	}
	else if (object->plane != NULL)
		return (hit_plane(object->plane, ray), ray->distance);
	return (-1.0);
}

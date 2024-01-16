
#include "mini_rt.h"

void	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_vector	sphere_to_ray_origin;
	double		dir_len_sq;
	double		projection_len;
	double		radius_sq;
	double		discriminant;

	sphere_to_ray_origin = vec_subtract(ray->origin, sphere->cords);
	dir_len_sq = dot_product(ray->direction, ray->direction);
	projection_len = 2.0 * dot_product(sphere_to_ray_origin, ray->direction);
	radius_sq = dot_product(sphere_to_ray_origin, sphere_to_ray_origin) - (sphere->diameter / 2)
		* (sphere->diameter / 2);
	discriminant = projection_len * projection_len - 4 * dir_len_sq * radius_sq;
	if (discriminant < 0)
	{
		ray->distance = -1;
		return ;
	}
	ray->distance = (-projection_len - sqrt(discriminant)) / (2.0 * dir_len_sq);
	ray->ray_colour = sphere->colour;
	ray->hit_point = ray_at(*ray, ray->distance);
}

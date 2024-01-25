
#include "mini_rt.h"

/**
 * @brief Checks if a ray hits a specific sphere object
 * @param sphere the sphere object to check
 * @param ray the ray to check
 * @return sets the distance to -1 in case of no hit
 */
void hit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_vector	sphere_to_ray_origin;
	double		dir_len_sq;
	double		proj_len;
	double		radius_sq;
	double		discriminant;
	double		t1;
	double		t2;

	sphere_to_ray_origin = vec_subtract(ray->origin, sphere->cords);
	dir_len_sq = dot_product(ray->direction, ray->direction);
	proj_len = dot_product(sphere_to_ray_origin, ray->direction);
	radius_sq = dot_product(sphere_to_ray_origin, sphere_to_ray_origin) - (sphere->diameter / 2) * (sphere->diameter / 2);
	discriminant = proj_len * proj_len - dir_len_sq * radius_sq;
	if (discriminant < 0)
	{
		ray->distance = -1;
		return;
	}
	t1 = (-proj_len - sqrt(discriminant)) / dir_len_sq;
	t2 = (-proj_len + sqrt(discriminant)) / dir_len_sq;
	if (t1 < 0 && t2 < 0)
	{
		ray->distance = -1;
		return ;
	}
	else if (t1 > 0 && t2 > 0)
		ray->distance = fmin(t1, t2);
	else
		ray->distance = fmax(t1, t2);
	ray->ray_colour = sphere->colour;
	ray->hit_point = ray_at(*ray, ray->distance);
	ray->surface_norm = normalize_vector(vec_subtract(ray->hit_point, sphere->cords));
	if (!(t1 > 0 && t2 > 0))
		ray->surface_norm = vec_scalar_multiply(ray->surface_norm, -1);
}

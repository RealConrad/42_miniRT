#include "mini_rt.h"

static double		hit_sphere(t_sphere *sphere, t_ray ray);
static double		hit_plane(t_plane *plane, t_ray ray);
static double		hit_cylinder(t_cylinder *cylinder, t_ray ray);

double	hit_object(t_object *object, t_ray ray)
{
	if (object->sphere != NULL)
		return (hit_sphere(object->sphere, ray));
	else if (object->cylinder != NULL)
		return (hit_cylinder(object->cylinder, ray));
	else if (object->plane != NULL)
		return (hit_plane(object->plane, ray));
	return (-1.0);
}

static double	hit_sphere(t_sphere *sphere, t_ray ray)
{
	t_vector	sphere_to_ray_origin;
	double		dir_len_sq;
	double		projection_len;
	double		radius_sq;
	double		discriminant;

	sphere_to_ray_origin = vec_subtract(ray.origin, sphere->cords);
	dir_len_sq = dot_product(ray.direction, ray.direction);
	projection_len = 2.0 * dot_product(sphere_to_ray_origin, ray.direction);
	radius_sq = dot_product(sphere_to_ray_origin, sphere_to_ray_origin) - (sphere->diameter / 2)
		* (sphere->diameter / 2);
	discriminant = projection_len * projection_len - 4 * dir_len_sq * radius_sq;
	if (discriminant < 0)
		return (-1.0);
	return ((-projection_len - sqrt(discriminant)) / (2.0 * dir_len_sq));
}

static double	hit_plane(t_plane *plane, t_ray ray)
{
	double	d_pro;
	double	distance;

	d_pro = dot_product(plane->threed_vec, ray.direction);
	if (ft_dabs(d_pro) < EPSILON)
		return (-1.0);
	distance = dot_product(vec_subtract(plane->cords, ray.origin),
			plane->threed_vec) / d_pro;
	if (distance < 0)
		return (-1.0);
	return (distance);
}

double hit_cylinder(t_cylinder *cylinder, t_ray ray)
{
	t_vector X = vec_subtract(ray.origin, cylinder->cords);  // Vector from ray origin to cylinder center
	t_vector D = normalize_vector(ray.direction);  // Ray direction
	t_vector V = normalize_vector(cylinder->axis);  // Cylinder axis
	double r = cylinder->diameter / 2.0;  // Cylinder radius
	double half_height = cylinder->height / 2.0; // Half of the cylinder's height

	double a = dot_product(D, D) - pow(dot_product(D, V), 2);
	double b = 2 * (dot_product(D, X) - (dot_product(D, V) * dot_product(X, V)));
	double c = dot_product(X, X) - pow(dot_product(X, V), 2) - r * r;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return -1.0; // No intersection with the cylinder's side
	}

	double t0 = (-b - sqrt(discriminant)) / (2 * a);
	double t1 = (-b + sqrt(discriminant)) / (2 * a);

	// Check if the intersections are within the bounds of the cylinder caps
	bool within_bounds_t0 = false;
	bool within_bounds_t1 = false;
	double m0 = dot_product(D, V) * t0 + dot_product(X, V);
	double m1 = dot_product(D, V) * t1 + dot_product(X, V);

	// Check bounds for t0
	if (m0 >= -half_height && m0 <= half_height)
		within_bounds_t0 = true;
	if (m1 >= -half_height && m1 <= half_height)
		within_bounds_t1 = true;
	if (within_bounds_t0 && t0 > 0)
	{
		if (within_bounds_t1 && t1 > 0)
			return fmin(t0, t1); // Both are within bounds, return the closest one
		return t0; // Only t0 is within bounds
	}
	if (within_bounds_t1 && t1 > 0)
		return t1; // Only t1 is within bounds
	return -1.0; // No valid intersection within bounds
}

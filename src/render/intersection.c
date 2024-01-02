#include "mini_rt.h"

static bool		check_sphere_intersection(t_sphere *sphere, t_ray ray);
static double	dot_product(t_vector v1, t_vector v2);

bool	check_object_intersection(t_object *object, t_ray ray)
{
	bool	result;

	result = false;
	if (object->sphere)
		result = check_sphere_intersection(object->sphere, ray);
	return (result);
}

static bool	check_sphere_intersection(t_sphere *sphere, t_ray ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;

	oc = vec_subtract(ray.origin, sphere->cords);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) - sphere->diameter * sphere->diameter / 4;
	if ((b * b - 4 * a * c) < 0)
		return (false);
	return (true);
}

/**
 * @brief Takes 2 vectors and returns a single scalar value. This works
 * by multiplying the 2 vectors elements.
 * @param v1 
 * @param v2 
 * @return 
 */
static double	dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

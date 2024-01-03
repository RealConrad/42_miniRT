#include "mini_rt.h"

static double		hit_sphere(t_sphere *sphere, t_ray ray);
static double		dot_product(t_vector v1, t_vector v2);

double	hit_object(t_object *object, t_ray ray)
{
	if (object->sphere)
		return (hit_sphere(object->sphere, ray));
	return (-5.0);
}

static double	hit_sphere(t_sphere *sphere, t_ray ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vec_subtract(ray.origin, sphere->cords);
	a = dot_product(ray.direction, ray.direction);
	b = 2.0 * dot_product(oc, ray.direction);
	c = dot_product(oc, oc) -( sphere->diameter / 2) * (sphere->diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	return ((-b - sqrt(discriminant)) / (2.0 * a));
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

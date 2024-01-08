#include "mini_rt.h"

static double		hit_sphere(t_sphere *sphere, t_ray ray);
static double		hit_plane(t_plane *plane, t_ray ray);

double	hit_object(t_object *object, t_ray ray)
{
	if (object->sphere != NULL)
		return (hit_sphere(object->sphere, ray));
	else if (object->plane != NULL)
		return (hit_plane(object->plane, ray));
	return (-1.0);
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
	c = dot_product(oc, oc) - (sphere->diameter / 2)
		* (sphere->diameter / 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

static double	hit_plane(t_plane *plane, t_ray ray)
{
	double	d_pro;
	double	t;

	d_pro = dot_product(plane->threed_vec, ray.direction);
	if (ft_dabs(d_pro) < EPSILON)
		return (-1.0);
	t = dot_product(vec_subtract(plane->cords, ray.origin),
			plane->threed_vec) / d_pro;
	if (t < 0)
		return (-1.0);
	return (t);
}

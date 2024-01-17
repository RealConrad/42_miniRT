#include "mini_rt.h"

static void		init_cy_data(t_cy_data *data, t_ray *ray, t_cylinder *cylinder);
static void 	check_side_intersection(t_cy_data *data, t_cylinder *cylinder);
static void 	check_cap_intersection(t_cy_data *data, t_cylinder *cylinder, t_ray *ray);
static bool 	check_cap(t_cy_data *data, t_vector cap_center, double t_cap, t_ray *ray);
static void 	find_closest_intersection(t_ray *ray, t_cy_data *data);

void	hit_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_cy_data	data;
	
	init_cy_data(&data, ray, cylinder);
	if (data.discriminant < 0)
	{
		ray->distance = -1;
		return ;
	}
	check_side_intersection(&data, cylinder);
	check_cap_intersection(&data, cylinder, ray);
	find_closest_intersection(ray, &data);
	ray->ray_colour = cylinder->colour;
	ray->hit_point = ray_at(*ray, ray->distance);
}

static void init_cy_data(t_cy_data *data, t_ray *ray, t_cylinder *cylinder)
{
	data->x = vec_subtract(ray->origin, cylinder->cords);
	data->d = normalize_vector(ray->direction);
	data->v = normalize_vector(cylinder->axis);
	data->radius = cylinder->diameter / 2.0;
	data->a = dot_product(data->d, data->d) - pow(dot_product(data->d, data->v), 2);
	data->b = 2 * (dot_product(data->d, data->x) - (dot_product(data->d, data->v) * dot_product(data->x, data->v)));
	data->c = dot_product(data->x, data->x) - pow(dot_product(data->x, data->v), 2) - data->radius * data->radius;
	data->discriminant = data->b * data->b - 4 * data->a * data->c;
}


static void check_side_intersection(t_cy_data *data, t_cylinder *cylinder)
{
	double	half_height;
	double	m0;
	double	m1;

	half_height = cylinder->height / 2.0;
	data->within_bounds_d0 = false;
	data->within_bounds_d1 = false;
	data->d0 = (-data->b - sqrt(data->discriminant)) / (2 * data->a);
	data->d1 = (-data->b + sqrt(data->discriminant)) / (2 * data->a);
	m0 = dot_product(data->d, data->v) * data->d0 + dot_product(data->x, data->v);
	m1 = dot_product(data->d, data->v) * data->d1 + dot_product(data->x, data->v);
	if (m0 >= -half_height && m0 <= half_height)
		data->within_bounds_d0 = true;
	if (m1 >= -half_height && m1 <= half_height)
		data->within_bounds_d1 = true;
}

static void check_cap_intersection(t_cy_data *data, t_cylinder *cylinder, t_ray *ray)
{
	double		half_height;
	t_vector	cap_top_center;
	t_vector	cap_bottom_center;

	half_height = cylinder->height / 2.0;
	cap_top_center = vec_add(cylinder->cords, vec_scalar_multiply(data->v, half_height));
	cap_bottom_center = vec_subtract(cylinder->cords, vec_scalar_multiply(data->v, half_height));
	data->d_top_cap = (dot_product(cap_top_center, data->v) - dot_product(ray->origin, data->v)) / dot_product(ray->direction, data->v);
	data->d_bot_cap = (dot_product(cap_bottom_center, data->v) - dot_product(ray->origin, data->v)) / dot_product(ray->direction, data->v);
	data->hit_top_cap = check_cap(data, cap_top_center, data->d_top_cap, ray);
	data->hit_bot_cap = check_cap(data, cap_bottom_center, data->d_bot_cap, ray);
}


static bool check_cap(t_cy_data *data, t_vector cap_center, double t_cap, t_ray *ray)
{
	t_vector	p_cap;
	t_vector	p_cap_to_center;

	p_cap = vec_add(ray->origin, vec_scalar_multiply(ray->direction, t_cap));
	p_cap_to_center = vec_subtract(p_cap, cap_center);
	if (dot_product(p_cap_to_center, p_cap_to_center) <= (data->radius * data->radius) && t_cap > 0)
		return (true);
	return (false);
}


static void find_closest_intersection(t_ray *ray, t_cy_data *data)
{
	double	d_cap;
	double	d_side;

	d_cap = find_closest_cap(data);
	d_side = find_closest_side(data);
	if (d_cap > 0 && (d_cap < d_side || d_side <= 0))
		ray->distance = d_cap;
	else if (d_side > 0)
		ray->distance = d_side;
	else
		ray->distance = -1.0;
}

/*
static void hit_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_vector X = vec_subtract(ray->origin, cylinder->cords);  // Vector from ray origin to cylinder center
	t_vector D = normalize_vector(ray->direction);  // Ray direction
	t_vector V = normalize_vector(cylinder->axis);  // Cylinder axis
	double r = cylinder->diameter / 2.0;  // Cylinder radius
	double half_height = cylinder->height / 2.0; // Half of the cylinder's height

	double a = dot_product(D, D) - pow(dot_product(D, V), 2);
	double b = 2 * (dot_product(D, X) - (dot_product(D, V) * dot_product(X, V)));
	double c = dot_product(X, X) - pow(dot_product(X, V), 2) - r * r;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		ray->distance = -1;
		return ; // No intersection with the cylinder's side
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

	// Calculate the planes for the caps
	t_vector cap_top_center = vec_add(cylinder->cords, vec_scalar_multiply(V, half_height));
	t_vector cap_bottom_center = vec_subtract(cylinder->cords, vec_scalar_multiply(V, half_height));

	// Intersection with the top cap
	double t_top_cap = (dot_product(cap_top_center, V) - dot_product(ray->origin, V)) / dot_product(ray->direction, V);
	t_vector P_top_cap = vec_add(ray->origin, vec_scalar_multiply(ray->direction, t_top_cap));
	t_vector P_top_cap_to_center = vec_subtract(P_top_cap, cap_top_center);
	bool intersects_top_cap = dot_product(P_top_cap_to_center, P_top_cap_to_center) <= (r * r) && t_top_cap > 0;

	// Intersection with the bottom cap
	double t_bottom_cap = (dot_product(cap_bottom_center, V) - dot_product(ray->origin, V)) / dot_product(ray->direction, V);
	t_vector P_bottom_cap = vec_add(ray->origin, vec_scalar_multiply(ray->direction, t_bottom_cap));
	t_vector P_bottom_cap_to_center = vec_subtract(P_bottom_cap, cap_bottom_center);
	bool intersects_bottom_cap = dot_product(P_bottom_cap_to_center, P_bottom_cap_to_center) <= (r * r) && t_bottom_cap > 0;

	// Determine the closest intersection point
	double t_cap = -1.0;
	if (intersects_top_cap && (!intersects_bottom_cap || t_top_cap < t_bottom_cap))
		t_cap = t_top_cap;
	else if (intersects_bottom_cap)
		t_cap = t_bottom_cap;

	// Compare with side intersection
	if (within_bounds_t0 && t0 > 0) {
		if (t_cap > 0 && t_cap < t0)
		{
			ray->distance = t_cap; // Cap intersection is closer
			return ;
		}
		if (within_bounds_t1 && t1 > 0 && t1 < t0)
		{
			ray->distance = t1;
			return ; // Bottom of the side intersection is closer
		}
		ray->distance = t0;
		return ; // Top of the side intersection is closer
	}
	if (within_bounds_t1 && t1 > 0)
	{
		if (t_cap > 0 && t_cap < t1)
		{
			ray->distance = t_cap;
			return ; // Cap intersection is closer
		}
		ray->distance = t1;
		return ; // Only the side intersection is within bounds
	}
	if (t_cap > 0)
	{
		ray->distance = t_cap;
		return ; // Only the cap intersection is within bounds
	}
	ray->distance = -1.0; // no valid intersection
}
*/
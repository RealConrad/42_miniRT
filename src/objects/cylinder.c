#include "mini_rt.h"

static void		init_cy_data(t_cy_data *data, t_ray *ray, t_cylinder *cylinder);
static void 	check_cap_intersection(t_ray *ray, t_cylinder *cylinder, t_cy_data *data);
static void 	find_closest_intersection(t_ray *ray, t_cy_data *data);
static void 	check_side_intersection(t_ray *ray, t_cylinder *cylinder, t_cy_data *data);

void	hit_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_cy_data	cy_data;
	
	init_cy_data(&cy_data, ray, cylinder);
	if (cy_data.discriminant < 0)
	{
		ray->distance = -1;
		return ;
	}
	check_side_intersection(ray, cylinder, &cy_data);
	check_cap_intersection(ray, cylinder, &cy_data);
	find_closest_intersection(ray, &cy_data);
}

static void	find_closest_intersection(t_ray *ray, t_cy_data *data)
{
	double closest_intersection;

	closest_intersection = INFINITY;
	if (data->top_cap_hit && (!data->bot_cap_hit || data->top_cap < data->bot_cap))
		closest_intersection = data->top_cap;
	else if (data->bot_cap_hit)
		closest_intersection = data->bot_cap;

	if (data->within_bounds_d0 && data->d0 > 0 && data->d0 < closest_intersection)
		closest_intersection = data->d0;
	if (data->within_bounds_d1 && data->d1 > 0 && data->d1 < closest_intersection)
		closest_intersection = data->d1;


	if (closest_intersection == INFINITY)
		ray->distance = -1.0;
	else
		ray->distance = closest_intersection;
}



static void	init_cy_data(t_cy_data *data, t_ray *ray, t_cylinder *cylinder)
{
	data->ray_origin_to_cy_center = vec_subtract(ray->origin, cylinder->cords);
	data->radius = cylinder->diameter / 2.0;
	data->quad_coeff_a = dot_product(ray->direction, ray->direction) - pow(dot_product(ray->direction, cylinder->axis), 2);
	data->quad_coeff_b = dot_product(ray->direction, data->ray_origin_to_cy_center);
	data->quad_coeff_b = data->quad_coeff_b - (dot_product(ray->direction, cylinder->axis) * dot_product(data->ray_origin_to_cy_center, cylinder->axis));
	data->quad_coeff_c = dot_product(data->ray_origin_to_cy_center, data->ray_origin_to_cy_center);
	data->quad_coeff_c = data->quad_coeff_c - pow(dot_product(data->ray_origin_to_cy_center, cylinder->axis), 2) - data->radius * data->radius;
	data->discriminant = data->quad_coeff_b * data->quad_coeff_b - 4 * data->quad_coeff_a * data->quad_coeff_c;

	data->d0 = (-data->quad_coeff_b - sqrt(data->discriminant)) / (2 * data->quad_coeff_a);
	data->d1 = (-data->quad_coeff_b + sqrt(data->discriminant)) / (2 * data->quad_coeff_a);
	data->within_bounds_d0 = false;
	data->within_bounds_d1 = false;
}

static void	check_side_intersection(t_ray *ray, t_cylinder *cylinder,
	t_cy_data *data)
{
	double	m0;
	double	m1;
	double	half_height;

	half_height = cylinder->height / 2.0;
	m0 = dot_product(ray->direction, cylinder->axis) * data->d0;
	m0 = m0 + dot_product(data->ray_origin_to_cy_center, cylinder->axis);
	m1 = dot_product(ray->direction, cylinder->axis) * data->d1;
	m1 = m1 + dot_product(data->ray_origin_to_cy_center, cylinder->axis);

	if (m0 >= -half_height && m0 <= half_height)
		data->within_bounds_d0 = true;
	if (m1 >= -half_height && m1 <= half_height)
		data->within_bounds_d1 = true;
}

static void	check_cap_intersection(t_ray *ray, t_cylinder *cylinder,
	t_cy_data *data)
{
	t_vector	cap_center;
	t_vector	top_cap;
	t_vector	bottom_cap;

	data->top_cap_hit = false;
	data->bot_cap_hit = false;
	cap_center = vec_add(cylinder->cords, vec_scalar_multiply(cylinder->axis, cylinder->height / 2));
	data->top_cap = dot_product(cap_center, cylinder->axis) - dot_product(ray->origin, cylinder->axis);
	data->top_cap = data->top_cap / dot_product(ray->direction, cylinder->axis);
	top_cap = vec_add(ray->origin, vec_scalar_multiply(ray->direction, data->top_cap));
	top_cap = vec_subtract(top_cap, cap_center);
	if (dot_product(top_cap, top_cap) <= (data->radius * data->radius) && data->top_cap > 0)
		data->top_cap_hit = true;
	cap_center = vec_subtract(cylinder->cords, vec_scalar_multiply(cylinder->axis, cylinder->height / 2));
	data->bot_cap = dot_product(cap_center, cylinder->axis) - dot_product(ray->origin, cylinder->axis);
	data->bot_cap = data->bot_cap / dot_product(ray->direction, cylinder->axis);
	bottom_cap = vec_add(ray->origin, vec_scalar_multiply(ray->direction, data->bot_cap));
	bottom_cap = vec_subtract(bottom_cap, cap_center);
	if (dot_product(bottom_cap, bottom_cap) <= (data->radius * data->radius) && data->bot_cap > 0)
		data->bot_cap_hit = true;
}


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
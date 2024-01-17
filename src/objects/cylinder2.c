#include "mini_rt.h"

/**
 * @brief Returns which cap is closer (bottom or top)
 * @param data The data that contains the discriminant and
 * cylinder data 
 * @return The closer distance or -1 if no intersection
 */
double	find_closest_cap(t_cy_data *data)
{
	if (data->hit_top_cap && (!data->hit_bot_cap || data->d_top_cap < data->d_bot_cap))
		return (data->d_top_cap);
	else if (data->hit_bot_cap)
		return (data->d_bot_cap);
	return (-1.0);
}

/**
 * @brief Returns the closest side hit
 * @param data The data that contains the discriminant and
 * cylinder data
 * @return The closer hit distance or -1 if no intersection
 */
double	find_closest_side(t_cy_data *data)
{
	if (data->within_bounds_d0 && data->d0 > 0)
	{
		if (data->within_bounds_d1 && data->d1 > 0 && data->d1 < data->d0)
			return (data->d1);
		return (data->d0);
	}
	else if (data->within_bounds_d1 && data->d1 > 0)
		return (data->d1);
	return (-1.0);
}

/**
 * @brief Calculates the surface normal at the point of intersection
 * 
 * It handles 2 cases: Intersection with the caps and sides.
 * For the sides, the normal is calculated as the normalized vector form
 * axis to hit point. For the caps the normal is just the axis 
 * (positive if top cap, negative for bottom cap). 
 * @param data cylinder related data
 * @param ray The ray which contains the hit point
 * @param cylinder The cylinder to calculate the surface normal for
 * @return The calculated surface normal
 */
t_vector	get_cylinder_surface_norm(t_cy_data data, t_ray *ray, t_cylinder *cylinder)
{
	t_vector	norm;
	t_vector	axis_to_intersection;
	t_vector	closest_point;
	double		proj_length;
	
	if (ray->distance == data.d_bot_cap || ray->distance == data.d_top_cap)
	{
		if (ray->distance == data.d_top_cap)
			return (cylinder->axis);
		else
			return ((t_vector){-cylinder->axis.x, -cylinder->axis.y, -cylinder->axis.z});
	}
	axis_to_intersection = vec_subtract(ray->hit_point, cylinder->cords);
	proj_length = dot_product(axis_to_intersection, cylinder->axis);
	closest_point = vec_add(cylinder->cords, vec_scalar_multiply(cylinder->axis, proj_length));
	norm = normalize_vector(vec_subtract(ray->hit_point, closest_point));
	return (norm);
}

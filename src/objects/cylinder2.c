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

	if (ray->distance == data.d_bot_cap || ray->distance == data.d_top_cap)
	{
		if (ray->distance == data.d_top_cap)
			return (normalize_vector(cylinder->axis));
		else
			return (normalize_vector(vec_scalar_multiply(cylinder->axis, -1)));
	}
	// THIS IS MARKUS CODE:
	cylinder->axis = normalize_vector(cylinder->axis);
	t_vector x = vec_subtract(ray->origin, cylinder->cords);
	double m = dot_product(ray->direction, vec_scalar_multiply(cylinder->axis, ray->distance)) + dot_product(x, cylinder->axis);
	norm = (vec_subtract(vec_subtract(ray->hit_point, cylinder->cords), vec_scalar_multiply(cylinder->axis, m)));
	return (normalize_vector(norm));
}

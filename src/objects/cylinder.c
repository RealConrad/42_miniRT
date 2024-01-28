#include "mini_rt.h"

static void		init_cy_data(t_cy_data *data, t_ray *ray, t_cylinder *cylinder);
static void 	check_side_intersection(t_cy_data *data, t_cylinder *cylinder);
static void 	check_cap_intersection(t_cy_data *data, t_cylinder *cylinder, t_ray *ray);
static bool 	check_cap(t_cy_data *data, t_vector cap_center, double t_cap, t_ray *ray);
static void 	find_closest_intersection(t_ray *ray, t_cy_data *data);

/**
 * @brief Checks if given `ray` intersects or hits the given `cylinder`
 * @param cylinder The cylinder to check if the ray hits
 * @param ray The ray to check if it intersects with a cylinder
 */
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
	ray->hit_point = ray_at(*ray, ray->distance);
	ray->ray_colour = normalize_colour(cylinder->colour);
	if (ray->distance != -1)
		ray->surface_norm = get_cylinder_surface_norm(data, ray, cylinder);
}

/**
 * @brief Initializes data for the given `data` variable.
 * 
 * This function calculates the discriminant, radius and normalizes
 * cylinder axis and ray direction.
 * 
 * @param data The data to be initialzed
 * @param ray The given ray we checking for intersection
 * @param cylinder The given cylinder to check for intersection
 */
static void init_cy_data(t_cy_data *data, t_ray *ray, t_cylinder *cylinder)
{
	data->x = vec_subtract(ray->origin, cylinder->cords);
	data->d = (ray->direction);
	data->v = normalize_vector(normalize_vector(cylinder->axis));
	// printf("\n\nCYLINDER:\n");
	// t_print_vector(data->d);
	// t_print_vector(data->v);
	// exit(0);
	data->radius = cylinder->diameter * 0.5;
	data->a = dot_product(data->d, data->d) - pow(dot_product(data->d, data->v), 2);
	data->b = 2 * (dot_product(data->d, data->x) - (dot_product(data->d, data->v) * dot_product(data->x, data->v)));
	data->c = dot_product(data->x, data->x) - pow(dot_product(data->x, data->v), 2) - data->radius * data->radius;
	data->discriminant = data->b * data->b - 4 * data->a * data->c;
}


/**
 * @brief Checks if the ray intersects a cylinder side.
 * 
 * Calculates the 2 potential intersection points of a ray with a cylinder.
 * We calculate 2 points because of the curved nature of a cylinder.
 * `data->d0` is the entry intersection and `data->d1` is the exit point
 * It then checks if the intersection is iwthin the height limit of the
 * cylinder
 * @param data The data which contains discriminant and cylidner data
 * @param cylinder The cylinder to check if side is intersected or not
 */
static void check_side_intersection(t_cy_data *data, t_cylinder *cylinder)
{
	double	half_height;
	double	m0;
	// double	m1;

	half_height = cylinder->height / 2.0;
	data->within_bounds_d0 = false;
	data->within_bounds_d1 = false;
	data->d0 = (-data->b - sqrt(data->discriminant)) / (2 * data->a);
	// data->d1 = (-data->b + sqrt(data->discriminant)) / (2 * data->a);
	m0 = dot_product(data->d, data->v) * data->d0 + dot_product(data->x, data->v);
	// m1 = dot_product(data->d, data->v) * data->d1 + dot_product(data->x, data->v);
	if (m0 >= -half_height && m0 <= half_height)
		data->within_bounds_d0 = true;
	// if (m1 >= -half_height && m1 <= half_height)
	// 	data->within_bounds_d1 = true;
}

/**
 * @brief Checks if the given ray intersects a cylinder caps
 * @param data The data which contains discriminant and cylinder data
 * @param cylinder The cylinder to check if the ray hits the caps
 * @param ray The ray to check if it intersects a cap
 */
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


/**
 * @brief Checks if the ray intersects/hits is within the cap
 * @param data The data that contains the discriminant and cylinder data
 * @param cap_center The center of the cap to be checked
 * @param t_cap The distance to the cap
 * @param ray The ray to check if it intersects a cap
 * @return True if the ray intersects a cap, else false
 */
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

/**
 * @brief Finds which intersection is closer, side or cap and
 * then sets the `ray->distance` to the closer one.
 * @param ray The ray to set the distance for
 * @param data The data used to determine which is closer
 */
static void find_closest_intersection(t_ray *ray, t_cy_data *data)
{
	double	d_cap;
	double	d_side;

	d_side = -1.0;
	d_cap = find_closest_cap(data);
	if (data->within_bounds_d0)
		d_side = data->d0;
	if (d_cap > 0 && (d_cap < d_side || d_side < 0))
		ray->distance = d_cap;
	else if (d_side > 0)
		ray->distance = d_side;
	else
		ray->distance = -1.0;
}

// static void find_closest_intersection(t_ray *ray, t_cy_data *data)
// {
//     double d_cap;
//     double d_side;

//     // Initialize d_side to a large number or infinity
//     d_side = DBL_MAX; // or a very large number if DBL_MAX is not available
//     d_cap = find_closest_cap(data);

//     // Check if the intersection with the cylinder's side (d0) is valid and closer
//     if (data->within_bounds_d0 && data->d0 > 0) {
//         d_side = data->d0;
//     }

//     // Check if the intersection with the cylinder's side (d1) is valid and closer
//     if (data->within_bounds_d1 && data->d1 > 0 && data->d1 < d_side) {
//         d_side = data->d1;
//     }

//     // Determine the closest intersection
//     if (d_cap > 0 && (d_cap < d_side)) {
//         ray->distance = d_cap; // Cap intersection is closer
//     } else if (d_side < DBL_MAX) {
//         ray->distance = d_side; // Side intersection is closer
//     } else {
//         ray->distance = -1.0; // No valid intersection
//     }
// }
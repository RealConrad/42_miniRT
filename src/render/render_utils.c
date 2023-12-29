#include "mini_rt.h"

static t_colour	blend_colour(t_colour c1, t_colour c2, double t);
static t_vector	normalize_vector(t_vector v);

uint32_t	get_rgb(t_colour colour)
{
	return ((colour.r << 24) | (colour.g << 16) | (colour.b << 8) | 0xFF);
}

t_colour	get_ray_colour(t_ray ray)
{
	t_vector	normalized_ray_direction;
	double		ratio;
	t_colour	white;
	t_colour	blue;

	normalized_ray_direction = normalize_vector(ray.direction);
	ratio = 0.5  * (normalized_ray_direction.y + 1.0);
	white = (t_colour){255, 255, 255};
	blue = (t_colour){128, 178, 255};
	return (blend_colour(blue, white, ratio));
}

/**
 * @brief Blends colour based on given ratio
 * @param c1 
 * @param c2 
 * @param t 
 * @return 
 */
static t_colour	blend_colour(t_colour c1, t_colour c2, double ratio)
{
	t_colour	result;

	result.r = (int)((1 - ratio) * c1.r + ratio * c2.r);
	result.g = (int)((1 - ratio) * c1.g + ratio * c2.g);
	result.b = (int)((1 - ratio) * c1.b + ratio * c2.b);
	return (result);
}

/**
 * @brief Scales vector to length of 1 (normalizes a vector)
 * @param v 
 * @return 
 */
static t_vector	normalize_vector(t_vector v)
{
	double		length;
	t_vector	unit;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	unit.x = v.x / length;
	unit.y = v.y / length;
	unit.z = v.z / length;
	return (unit);
}

#include "mini_rt.h"

/**
 * @brief Converts the given `colour` to a 32-bit RGBA value.
 * 
 * `mlx_put_pixel` only accepts a 32-Bit RGBA value
 * @param colour The colour to convert
 * @return The 32-bit RGBA.
 */
uint32_t	get_rgb(t_colour colour)
{
	return (((int)colour.r << 24) | ((int)colour.g << 16) | ((int)colour.b << 8) | 255);
}


/**
 * @brief Scales the given colour by `scalar`
 * @param c The colour to scale
 * @param scalar A double to scale each colour element by
 * @return A newly scaled colour.
 */
t_colour colour_scalar_multiply(t_colour c, double scalar)
{
	t_colour	result;

	result.r = c.r * scalar;
	result.g = c.g * scalar;
	result.b = c.b * scalar;
	return (result);
}

/**
 * @brief Gets a sky colour based on the direction of the ray.
 * 
 * Gets the background colour for a given scene based on the 
 * y-component of the ray direction.
 * @param ray The given ray to determine the colour based on
 * direction
 * @return A new "sky" colour.
 */
t_colour	get_sky_background(t_ray *ray)
{
	t_colour	blue;
	t_colour	white;
	t_colour	result;
	double		t;

	blue = (t_colour){70 / 255.0, 130 / 255.0, 180 / 255.0};
	white = (t_colour){1.0, 1.0, 1.0};
	t = 0.5 * (ray->direction.y + 1.0);
	result.r = (1.0 - t) * white.r + t * blue.r;
	result.g = (1.0 - t) * white.g + t * blue.g;
	result.b = (1.0 - t) * white.b + t * blue.b;
	return (result);
}

/**
 * @brief Normalizes a colour. Sets the value of an RGB colour
 * between 0-1.
 * @param colour The colour to normalize.
 * @return A newly normalized colour.
 */
t_colour	normalize_colour(t_colour colour)
{
	t_colour	result;

	result.r = colour.r / 255.0;
	result.g = colour.g / 255.0;
	result.b = colour.b / 255.0;
	return (result);
}

/**
 * @brief Ensures the given colour is within the valid
 * normalized range, 0-1. If and element is above 1, it
 * sets it to 1 and if its less than 0 it sets it to 0.
 * @param colour The colour to clamp.
 */
void	clamp_normalized_colour(t_colour *colour)
{
	if (colour->r > 1.0)
		colour->r = 1.0;
	if (colour->r < 0)
		colour->r = 0;

	if (colour->g > 1.0)
		colour->g = 1.0;
	if (colour->g < 0)
		colour->g = 0;

	if (colour->b > 1.0)
		colour->b = 1.0;
	if (colour->b < 0)
		colour->b = 0;
}

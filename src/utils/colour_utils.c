
#include "mini_rt.h"

uint32_t	get_rgb(t_colour colour)
{
	return (((int)colour.r << 24) | ((int)colour.g << 16) | ((int)colour.b << 8) | 255);
}

t_colour colour_multiply(t_colour c1, t_colour c2)
{
	t_colour	result;

	result.r = (c1.r / 255.0) * (c2.r / 255.0);
	result.g = (c1.g / 255.0) * (c2.g / 255.0);
	result.b = (c1.b / 255.0) * (c2.b / 255.0);
	return (result);
}
t_colour colour_scalar_multiply(t_colour c, double scalar)
{
	t_colour	result;

	result.r = c.r * scalar;
	result.g = c.g * scalar;
	result.b = c.b * scalar;
	return (result);
}

t_colour	get_sky_background(t_ray *ray)
{
	t_colour	blue;
	t_colour	white;
	t_colour	result;
	double		t;

	blue = (t_colour){70 / 255.0, 130 / 255.0, 180 / 255.0};
	white = (t_colour){1.0, 1.0, 1.0};
	// get position/height of sky
	t = 0.5 * (ray->direction.y + 1.0);
	result.r = (1.0 - t) * white.r + t * blue.r;
	result.g = (1.0 - t) * white.g + t * blue.g;
	result.b = (1.0 - t) * white.b + t * blue.b;
	return (result);
}

t_colour	normalize_colour(t_colour colour)
{
	t_colour	result;

	result.r = colour.r / 255.0;
	result.g = colour.g / 255.0;
	result.b = colour.b / 255.0;
	return (result);
}

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

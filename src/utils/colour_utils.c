
#include "mini_rt.h"

uint32_t	get_rgb(t_colour colour)
{
	return ((colour.r << 24) | (colour.g << 16) | (colour.b << 8) | 0xFF);
}

t_colour colour_multiply(t_colour c1, t_colour c2)
{
	t_colour	result;

	result.r = (c1.r / 255.0 * c2.r / 255.0) * 255;
	result.g = (c1.g / 255.0 * c2.g / 255.0) * 255;
	result.b = (c1.b / 255.0 * c2.b / 255.0) * 255;
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

	blue = (t_colour){70, 130, 180};
	white = (t_colour){255, 255, 255};
	// get position/height of sky
	t = 0.5 * (ray->direction.y + 1.0);
	result.r = (1.0 - t) * white.r + t * blue.r;
	result.g = (1.0 - t) * white.g + t * blue.g;
	result.b = (1.0 - t) * white.b + t * blue.b;
	return (result);
}

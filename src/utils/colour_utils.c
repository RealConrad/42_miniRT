
#include "mini_rt.h"

uint32_t	get_rgb(t_colour colour)
{
	return ((colour.r << 24) | (colour.g << 16) | (colour.b << 8) | 0xFF);
}

double	clamp(double value, double min, double max)
{
	return fmin(fmax(value, min), max);
}

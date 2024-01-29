
#include "mini_rt.h"

t_colour	add_phong_elements(t_colour a, t_colour d, t_colour s)
{
	t_colour	result;

	result.r = a.r + d.r + s.r;
	result.g = a.g + d.g + s.g;
	result.b = a.b + d.b + s.b;
	return (result);
}

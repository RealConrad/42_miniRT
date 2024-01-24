
#include "mini_rt.h"

/**
 * @brief Applies the ambient ratio and colour range to the objet colour
 * @param obj_colour The object colour to modify
 * @param amb the ambient light features
 * @return the modified colour
 */
t_colour	get_ambient_light(t_colour obj_colour, t_amb_light amb)
{
	t_colour	ambient_lighting;
	t_vector	ambient_ratio;

	ambient_ratio.x = (double)amb.colour.r / 255 * amb.light_ratio;
	ambient_ratio.y = (double)amb.colour.g / 255 * amb.light_ratio;
	ambient_ratio.z = (double)amb.colour.b / 255 * amb.light_ratio;
	ambient_lighting.r = obj_colour.r * ambient_ratio.x;
	ambient_lighting.g = obj_colour.g * ambient_ratio.y;
	ambient_lighting.b = obj_colour.b * ambient_ratio.z;
	return (ambient_lighting);
}
